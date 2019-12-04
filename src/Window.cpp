#include <iostream>

#include "Window.h"
#include "Time.h"
#include "objects/geometries/Terrain.h"

Window::Window() {
    setupCallbacks();
    initializeProgram();
    initializeObjects();

    // Initial size will not fire callback
    // force to fire
    resizeCallback(width, height);
}

void Window::initializeProgram() {
    try {
        shaders[0] = std::make_shared<Shader>("shaders/normal.vert",
                                              "shaders/normal.frag");
        shaders[1] = std::make_shared<Shader>("shaders/phong.vert",
                                              "shaders/reflection_map.frag");
    } catch (...) {
        std::cerr << "Failed to initialize shader program" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Window::initializeObjects() {
    glm::mat4 projection = glm::perspective(glm::radians(60.0f),
                                            float(width) / float(height), 0.1f, 1000.0f);

    auto cam = std::make_unique<Camera>(width, height);
    flyControl = scene.addChild(FreeFlying(cam.get(), glm::translate(glm::vec3(0, 0, 20))));
    cameras[0] = flyControl->addChild(std::move(cam));

    scene.addChild(Skybox());

    auto terrain = scene.addChild(Terrain(5, {0.0f, 0.0f, 0.0f, 0.0f}, 10.0f));
    walker = scene.addChild(TerrainWalker(terrain));

    walker->forwardKey = GLFW_KEY_Y;
    walker->backwardKey = GLFW_KEY_H;
    walker->leftKey = GLFW_KEY_G;
    walker->rightKey = GLFW_KEY_J;

    auto mesh = Mesh::fromObjFile("meshes/sphere.obj");
    mesh.useShader(std::make_shared<Shader>("shaders/phong.vert", "shaders/cartoon.frag"));
    mesh.transform.model = glm::scale(glm::vec3(0.1f, 0.1f, 0.1f));
    walker->addChild(mesh);

    cam = std::make_unique<Camera>(width, height);
    auto rotator = walker->addChild(FreeRotator(cam.get(), glm::translate(glm::vec3(0, 2.0f, 0))));
    cameras[1] = rotator->addChild(std::move(cam));
}

void Window::resizeCallback(int width, int height) {
#ifdef __APPLE__
    // In case your Mac has a retina display.
    glfwGetFramebufferSize(window, &width, &height);
#endif
    if (width && height) {
        this->width = width;
        this->height = height;
        // Set the viewport size.
        glViewport(0, 0, width, height);

        // Set the projection matrix.
        for (auto &cam:cameras) {
            cam->resize(width, height);
        }
    }
}

void Window::update() {
    scene.update();
}

void Window::draw() {
    scene.cull(cameras[0]->projection * cameras[0]->view);

    // Clear the color and depth buffers.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Render the object.
    scene.draw(glm::mat4(1.0f), *cameras[0]);

    // Swap buffers.
    glfwSwapBuffers(window);
}

void Window::setupCallbacks() {
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

void Window::keyCallback(int key, int scancode, int action, int mods) {
    // Check for a key press.
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                // Close the window. This causes the program to also terminate.
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
            case GLFW_KEY_N:
                std::swap(*shaders[0], *shaders[1]);
                break;
            case GLFW_KEY_C:
                std::swap(*cameras[0], *cameras[1]);
                break;
            default:
                break;
        }
        scene.onKeyPress(key, mods);
    } else if (action == GLFW_RELEASE) {
        scene.onKeyRelease(key, mods);
    }
}

void Window::mouseButtonCallback(int button, int action, int mods) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    switch (action) {
        case GLFW_PRESS:
            scene.onMouseButtonPress(button, mods, x, y);
            break;
        case GLFW_RELEASE:
            scene.onMouseButtonRelease(button, mods, x, y);
            break;
        default:
            break;
    }
}

void Window::cursorPosCallback(double x, double y) {
    scene.onMouseMove(x, y);
}

void Window::scrollCallback(double xoffset, double yoffset) {
}

void Window::loop() {
    // Enable depth buffering.
    glEnable(GL_DEPTH_TEST);
    // Related to shaders and z value comparisons for the depth buffer.
    glDepthFunc(GL_LEQUAL);
    // Enable face culling.
    glEnable(GL_CULL_FACE);
    // Set polygon drawing mode to fill front and back of each polygon.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Set clear color to black.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Enable stencil test
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);

    Time::reset();
    while (!glfwWindowShouldClose(window)) {
        Time::tick();
        glfwPollEvents();
        update();
        draw();
    }
}
