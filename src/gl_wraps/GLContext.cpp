#include <iostream>

#include "GLContext.h"

GLContext::GLContext() {
    // 4x antialiasing.
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create the GLFW window.
    window = glfwCreateWindow(width, height, "GLFW Starter Project", glfwGetPrimaryMonitor(), NULL);
    // Check if the window could not be created.
    if (!window) {
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetWindowUserPointer(window, this);

    // Make the context of the window.
    glfwMakeContextCurrent(window);
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Get info of GPU and supported OpenGL version.
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version supported: " << glGetString(GL_VERSION)
              << std::endl;

    //If the shading language symbol is defined.
#ifdef GL_SHADING_LANGUAGE_VERSION
    std::cout << "Supported GLSL version is: " <<
              glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
#endif

    // Set swap interval to 1.
    glfwSwapInterval(0);

    setupCallbacks();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

GLContext::~GLContext() {
    glfwDestroyWindow(window);
}

void GLContext::setupCallbacks() {
    // Set the key callback.
    glfwSetKeyCallback(window,
                       [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                           retrieve(window)->keyCallback(key, scancode, action, mods);
                       });
    // Set the window resize callback.
    glfwSetWindowSizeCallback(window,
                              [](GLFWwindow *window, int width, int height) {
                                  retrieve(window)->resizeCallback(width, height);
                              });
    // Set the mouse button callback.
    glfwSetMouseButtonCallback(window,
                               [](GLFWwindow *window, int button, int action, int mods) {
                                   retrieve(window)->mouseButtonCallback(button, action, mods);
                               });
    // Set the cursor position callback.
    glfwSetCursorPosCallback(window,
                             [](GLFWwindow *window, double x, double y) {
                                 retrieve(window)->cursorPosCallback(x, y);
                             });

    // Set the scroll callback.
    glfwSetScrollCallback(window,
                          [](GLFWwindow *window, double xoffset, double yoffset) {
                              retrieve(window)->scrollCallback(xoffset, yoffset);
                          });
}

void GLContext::resizeCallback(int width, int height) {
    this->width = width;
    this->height = height;
}
