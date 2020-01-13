#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>

#include "graphics_pipeline.hh"
#include "validation_layers.hh"
#include "vulkan_application.hh"

void VulkanApplication::run() {
  initVulkan();
  mainLoop();
  cleanup();
}


void VulkanApplication::initVulkan()
{
  instance.createSurface(window.window);

  devices = new Devices(instance);

  swap_chain = new SwapChain(window, instance, *devices);

  swap_chain->createImageViews();
  swap_chain->createRenderPass();
  swap_chain->createGraphicsPipeline();
  swap_chain->createFramebuffers();
  swap_chain->createCommandPool();
  swap_chain->createVertexBuffer();
  swap_chain->createIndexBuffer();
  swap_chain->createCommandBuffers();

  createSyncObjects();
}

void VulkanApplication::mainLoop()
{
  while (!glfwWindowShouldClose(window.window)) {
    glfwPollEvents();
    drawFrame();
  }
  vkDeviceWaitIdle(devices->device);
}

void VulkanApplication::createSyncObjects()
{
  imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
  renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
  inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
  imagesInFlight.resize(swap_chain->swapChainImages.size(), VK_NULL_HANDLE);

  VkSemaphoreCreateInfo semaphoreInfo = {};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkFenceCreateInfo fenceInfo = {};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
   if (vkCreateSemaphore(devices->device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
    vkCreateSemaphore(devices->device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
    vkCreateFence(devices->device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
    throw std::runtime_error("failed to create synchronization objects for a frame!");
   }
  }
}

void VulkanApplication::drawFrame()
{
  vkWaitForFences(devices->device, 1, &inFlightFences[currentFrame], VK_TRUE,
                  UINT64_MAX);

  uint32_t imageIndex;
  VkResult result = vkAcquireNextImageKHR(devices->device, swap_chain->swapChain,
                                          UINT64_MAX,
                                          imageAvailableSemaphores[currentFrame],
                                          VK_NULL_HANDLE, &imageIndex);

  if (result == VK_ERROR_OUT_OF_DATE_KHR)
  {
    swap_chain->recreateSwapChain();
    return;
  }
  else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
  {
    throw std::runtime_error("failed to acquire swap chain image!");
  }

  if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
   vkWaitForFences(devices->device, 1, &imagesInFlight[imageIndex], VK_TRUE,
                   UINT64_MAX);
  }
  imagesInFlight[imageIndex] = inFlightFences[currentFrame];

  VkSubmitInfo submitInfo = {};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

  VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
  VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores;
  submitInfo.pWaitDstStageMask = waitStages;

  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &swap_chain->commands.commandBuffers[imageIndex];

  VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores;

  vkResetFences(devices->device, 1, &inFlightFences[currentFrame]);

  if (vkQueueSubmit(devices->graphicsQueue, 1, &submitInfo,
                    inFlightFences[currentFrame]) != VK_SUCCESS)
  {
   throw std::runtime_error("failed to submit draw command buffer!");
  }

  VkPresentInfoKHR presentInfo = {};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

  presentInfo.waitSemaphoreCount = 1;
  presentInfo.pWaitSemaphores = signalSemaphores;

  VkSwapchainKHR swapChains[] = {swap_chain->swapChain};
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains;

  presentInfo.pImageIndices = &imageIndex;

  result = vkQueuePresentKHR(devices->presentQueue, &presentInfo);

  if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR
      || window.framebufferResized)
  {
      window.framebufferResized = false;
      swap_chain->recreateSwapChain();
  } else if (result != VK_SUCCESS) {
      throw std::runtime_error("failed to present swap chain image!");
  }

  currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void VulkanApplication::cleanup()
{
  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    vkDestroySemaphore(devices->device, renderFinishedSemaphores[i], nullptr);
    vkDestroySemaphore(devices->device, imageAvailableSemaphores[i], nullptr);
    vkDestroyFence(devices->device, inFlightFences[i], nullptr);
  }

  delete swap_chain;
  delete devices;
}

std::vector<const char*> VulkanApplication::getRequiredExtensions()
{
  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

  if (enableValidationLayers) {
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }

  return extensions;
}
