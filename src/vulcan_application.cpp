#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "graphics_pipeline.hh"
#include "validation_layers.hh"
#include "vulcan_application.hh"

void VulkanApplication::run() {
  initVulkan();
  mainLoop();
  cleanup();
}

void VulkanApplication::createSurface() {
    if (glfwCreateWindowSurface(instance.instance, window.window,
                                nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

void VulkanApplication::initVulkan()
{
  createSurface();
  devices.pickPhysicalDevice(instance.instance, surface);
  devices.createLogicalDevice(surface);

  devices.createSwapChain(surface);
  devices.createImageViews();
  devices.createRenderPass();
  devices.createGraphicsPipeline();
  devices.createFramebuffers();
  devices.createCommandPool(surface);
  devices.createCommandBuffers();
}

void VulkanApplication::mainLoop()
{
  while (!glfwWindowShouldClose(window.window)) {
    glfwPollEvents();
  }
}

void VulkanApplication::cleanup()
{
  devices.destroySwapChain();
  devices.destroyDevices();


  vkDestroySurfaceKHR(instance.instance, surface, nullptr);
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

bool VulkanApplication::checkValidationLayerSupport()
{
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  for (const char* layerName : validationLayers) {
    bool layerFound = false;

    for (const auto& layerProperties : availableLayers) {
      if (strcmp(layerName, layerProperties.layerName) == 0) {
        layerFound = true;
        break;
      }
    }

    if (!layerFound) {
      return false;
    }
  }

  return true;
}
