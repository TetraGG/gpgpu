#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

#include "devices.hh"
#include "window.hh"

class VulkanApplication
{
public:
  void run();

private:
  void createSurface();
  void initVulkan();
  void createInstance();
  void mainLoop();
  void cleanup();

  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
  bool checkValidationLayerSupport();
  std::vector<const char*> getRequiredExtensions();
  void setupDebugMessenger();

  Window window;

  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  VkSurfaceKHR surface;

  VulkanDevices devices;
};
