#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "instance.hh"
#include "queue_family_indices.hh"

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

class Devices
{
public:

  Devices(Instance& instance);
  ~Devices();

  Instance& instance;

  VkDevice device;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

  VkQueue graphicsQueue;
  VkQueue presentQueue;
private:
  void pickPhysicalDevice();
  void createLogicalDevice();

  bool isDeviceSuitable(VkPhysicalDevice device);
  bool checkDeviceExtensionSupport(VkPhysicalDevice device);

};
