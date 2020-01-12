#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

struct Instance
{
  Instance();
  ~Instance();

  void createSurface(GLFWwindow* window);

  VkInstance instance;

  VkSurfaceKHR surface;

  VkDebugUtilsMessengerEXT debugMessenger;
private:
  void createInstance();
  void setupDebugMessenger();
  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
};
