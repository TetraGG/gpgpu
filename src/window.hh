#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

const int WIDTH = 800;
const int HEIGHT = 600;

struct Window
{
  Window();
  ~Window();
  GLFWwindow* window;
};

