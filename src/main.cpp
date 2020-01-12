#include <iostream>
#include <stdexcept>

#include "vulkan_application.hh"

int main() {
    VulkanApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
