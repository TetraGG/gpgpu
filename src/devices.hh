#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "queue_family_indices.hh"

VkPhysicalDevice pickPhysicalDevice(VkInstance& instance, VkSurfaceKHR& surface);
void createLogicalDevice(VkPhysicalDevice& physicalDevice,
                         VkDevice& device,
                         VkQueue& graphicsQueue,
                         VkQueue& presentQueue,
                         VkSurfaceKHR& surface);
bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR& surface);
