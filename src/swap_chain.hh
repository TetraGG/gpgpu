#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

#include "command_buffers.hh"
#include "devices.hh"
#include "graphics_pipeline.hh"
#include "instance.hh"
#include "window.hh"

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct SwapChain
{
  SwapChain(Window& window, Instance& instance, Devices& devices);
  ~SwapChain();

  void recreateSwapChain();
  void cleanupSwapChain();

  void createImageViews();
  void createRenderPass();
  void createGraphicsPipeline();
  void createFramebuffers();
  void createCommandPool();
  void createCommandBuffers();
  void destroySwapChain();

  Window& window;
  Instance& instance;
  Devices& devices;

  VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
  SwapChainSupportDetails querySwapChainSupport();

  VkSwapchainKHR swapChain;
  std::vector<VkImage> swapChainImages;
  VkFormat swapChainImageFormat;
  VkExtent2D swapChainExtent;

  std::vector<VkFramebuffer> swapChainFramebuffers;

  std::vector<VkImageView> swapChainImageViews;

  GraphicsPipeline pipeline;

  CommandBuffers commands;
private:
  void createSwapChain();
};
