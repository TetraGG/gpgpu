#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulcan_application.hh"

const int WIDTH = 800;
const int HEIGHT = 600;

void VulkanApplication::run()
{
  initWindow();
  initVulkan();
  mainLoop();
  cleanup();
}

void VulkanApplication::initWindow()
{
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void VulkanApplication::initVulkan()
{
}

void VulkanApplication::mainLoop()
{
  while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
  }
}

void VulkanApplication::cleanup()
{
  glfwDestroyWindow(window);

  glfwTerminate();
}
