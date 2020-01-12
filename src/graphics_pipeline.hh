#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class GraphicsPipeline
{
public:
  void createGraphicsPipeline(VkDevice device, VkExtent2D& swapChainExtent);
  void createRenderPass(VkDevice& device, VkFormat& swapChainImageFormat);
  void destroyGraphicsPipeline(VkDevice& device);

  VkRenderPass renderPass;
  VkPipeline graphicsPipeline;
private:

  VkPipelineLayout pipelineLayout;
};
