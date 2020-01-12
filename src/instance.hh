#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

struct Instance
{
  Instance();
  ~Instance();

  VkInstance instance;

  VkDebugUtilsMessengerEXT debugMessenger;
private:
  void createInstance();
  void setupDebugMessenger();
  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
};
