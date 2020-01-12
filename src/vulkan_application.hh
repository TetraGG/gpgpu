#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

#include "devices.hh"
#include "instance.hh"
#include "swap_chain.hh"
#include "window.hh"

const int MAX_FRAMES_IN_FLIGHT = 2;

class VulkanApplication
{
public:
  void run();

private:
  void createSurface();
  void initVulkan();
  void mainLoop();
  void createSyncObjects();
  void drawFrame();
  void cleanup();

  std::vector<const char*> getRequiredExtensions();

  Window window;

  Instance instance;

  Devices* devices;
  SwapChain* swap_chain;

  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;
  std::vector<VkFence> imagesInFlight;
  size_t currentFrame = 0;
};
