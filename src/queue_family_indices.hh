#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <optional>

struct QueueFamilyIndices
{
  bool isComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }

  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;
};

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR& surface);
