#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

#include "devices.hh"
#include "instance.hh"
#include "window.hh"

class VulkanApplication
{
public:
  void run();

private:
  void createSurface();
  void initVulkan();
  void mainLoop();
  void cleanup();

  std::vector<const char*> getRequiredExtensions();

  Window window;

  Instance instance;

  Devices* devices;
};
