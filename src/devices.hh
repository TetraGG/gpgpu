#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "instance.hh"
#include "queue_family_indices.hh"

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
