#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "queue_family_indices.hh"

VkPhysicalDevice pickPhysicalDevice(VkInstance& instance);
void createLogicalDevice(VkPhysicalDevice& physicalDevice,
                         VkDevice& device,
                         VkQueue& graphicsQueue);
bool isDeviceSuitable(VkPhysicalDevice device);
