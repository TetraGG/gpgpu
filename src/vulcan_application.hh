#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class VulkanApplication
{
public:
  void run();

private:
  void initWindow();
  void initVulkan();
  void createInstance();
  void mainLoop();
  void cleanup();

  GLFWwindow* window;
  VkInstance instance;
};
