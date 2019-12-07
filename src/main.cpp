#include <iostream>
#include "gl_wraps/gl.h"
#include <GLFW/glfw3.h>

#include "Window.h"


void error_callback(int error, const char *description) {
    // Print error.
    std::cerr << description << std::endl;
    exit(EXIT_FAILURE);
}

void setup_glfw() {
    // Initialize GLFW.
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Setup error callback.
    glfwSetErrorCallback(error_callback);
}

int main(void) {
    setup_glfw();

    Window window;
    // Loop while GLFW window should stay open.
    window.loop();
}
