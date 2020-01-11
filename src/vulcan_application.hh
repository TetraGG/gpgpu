#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

#include "devices.hh"

const int WIDTH = 800;
const int HEIGHT = 600;

class VulkanApplication
{
public:
  void run();

private:
  void initWindow();
  void createSurface();
  void initVulkan();
  void createInstance();
  void mainLoop();
  void cleanup();

  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
  bool checkValidationLayerSupport();
  std::vector<const char*> getRequiredExtensions();
  void setupDebugMessenger();

  GLFWwindow* window;

  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  VkSurfaceKHR surface;

  VulkanDevices devices;
};
