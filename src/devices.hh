#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <optional>

struct QueueFamilyIndices
{
  bool isComplete() {
    return graphicsFamily.has_value();
  }

  std::optional<uint32_t> graphicsFamily;
};

VkPhysicalDevice pickPhysicalDevice(VkInstance& instance);

bool isDeviceSuitable(VkPhysicalDevice device);
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
