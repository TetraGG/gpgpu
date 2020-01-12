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

  swap_chain = new SwapChain(instance, *devices);

  swap_chain->createImageViews();
  swap_chain->createRenderPass();
  swap_chain->createGraphicsPipeline();
  swap_chain->createFramebuffers();
  swap_chain->createCommandPool();
  swap_chain->createCommandBuffers();
}

void VulkanApplication::mainLoop()
{
  while (!glfwWindowShouldClose(window.window)) {
    glfwPollEvents();
  }
}

void VulkanApplication::cleanup()
{
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
