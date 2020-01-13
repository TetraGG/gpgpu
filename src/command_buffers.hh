#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

struct CommandBuffers
{
  void createCommandPool(VkPhysicalDevice& physicalDevice, VkDevice& device,
                         VkSurfaceKHR& surface);
  void createCommandBuffers(VkDevice& device,
                                          VkRenderPass& renderPass,
  std::vector<VkFramebuffer>& swapChainFramebuffers,
  VkExtent2D& swapChainExtent,
  VkPipeline& graphicsPipeline,
  VkBuffer vertexBuffer);

  void cleanup(VkDevice& device);
  std::vector<VkCommandBuffer> commandBuffers;
  VkCommandPool commandPool;
};
