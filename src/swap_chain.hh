#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class VulkanSwapChain
{
public:
  void createSwapChain(VkPhysicalDevice physicalDevice,
                       VkDevice& device,
                       VkSurfaceKHR& surface);
  void createImageViews(VkDevice& device);
  void destroySwapChain(VkDevice& device);
private:
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
  SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device,
                                                VkSurfaceKHR& surface);

  VkSwapchainKHR swapChain;
  std::vector<VkImage> swapChainImages;
  VkFormat swapChainImageFormat;
  VkExtent2D swapChainExtent;

  std::vector<VkImageView> swapChainImageViews;
};
