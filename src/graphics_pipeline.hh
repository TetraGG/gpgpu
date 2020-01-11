#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class GraphicsPipeline
{
public:
  void createGraphicsPipeline(VkDevice device, VkExtent2D& swapChainExtent);
  void destroyGraphicsPipeline(VkDevice& device);

private:
  VkPipelineLayout pipelineLayout;
};
