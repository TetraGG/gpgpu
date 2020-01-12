#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "queue_family_indices.hh"
#include "swap_chain.hh"

class VulkanDevices
{
public:
  void pickPhysicalDevice(VkInstance& instance, VkSurfaceKHR& surface);
  void createLogicalDevice(VkSurfaceKHR& surface);
  void createSwapChain(VkSurfaceKHR& surface);
  void createImageViews();
  void createRenderPass();
  void createGraphicsPipeline();
  void createFramebuffers();
  void destroyDevices();
  void destroySwapChain();
  void createCommandPool(VkSurfaceKHR& surface);
  void createCommandBuffers();

  VkDevice device;
private:
  bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR& surface);
  bool checkDeviceExtensionSupport(VkPhysicalDevice device);

  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

  VkQueue graphicsQueue;
  VkQueue presentQueue;

  VulkanSwapChain swapChain;
};
