#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "instance.hh"
#include "queue_family_indices.hh"
#include "swap_chain.hh"

class Devices
{
public:

  Devices(Instance& instance);
  ~Devices();
  void pickPhysicalDevice();
  void createLogicalDevice();
  void createSwapChain();
  void createImageViews();
  void createRenderPass();
  void createGraphicsPipeline();
  void createFramebuffers();
  void destroyDevices();
  void destroySwapChain();
  void createCommandPool();
  void createCommandBuffers();

  Instance& instance;
  VkDevice device;
private:
  bool isDeviceSuitable(VkPhysicalDevice device);
  bool checkDeviceExtensionSupport(VkPhysicalDevice device);

  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

  VkQueue graphicsQueue;
  VkQueue presentQueue;

  VulkanSwapChain swapChain;
};
