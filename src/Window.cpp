#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <random>
#include <chrono>
#include "gl_wraps/gl.h"

#include "Window.h"
#include "Time.h"
#include "objects/Camera.h"
#include "objects/geometries/Skybox.h"
#include "objects/controls/FreeFlying.h"
#include "objects/geometries/Terrain.h"
#include "objects/controls/TerrainWalker.h"
#include "materials/NormalMaterial.h"
#include "materials/HeightMapMaterial.h"
#include "objects/geometries/LSystem.h"

Window::Window() {
    initializeObjects();

    // Initial size will not fire callback
    // force to fire
    resizeCallback(width, height);
}

void Window::initializeObjects() {
    glm::mat4 projection = glm::perspective(glm::radians(60.0f),
                                            float(width) / float(height), 0.1f, 1000.0f);

    scene.addChild(Skybox());
    auto terrain = scene.addChild(Terrain(8, {0.0f, 0.0f, 0.0f, 0.0f}, 50.0f));
    auto tex = std::make_shared<Texture2D>();
    tex->bind();
    tex->upload("textures/earth.png");
    tex->setFilter(GL_LINEAR, GL_LINEAR);
    tex->setWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    tex->unbind();
    auto material = std::make_unique<HeightMapMaterial>();
    material->tex = std::move(tex);
    material->maxHeight = terrain->boundingBox().max().y;
    material->minHeight = terrain->boundingBox().min().y;
    terrain->material = std::move(material);

    auto now = std::chrono::system_clock::now();
    std::default_random_engine gen(now.time_since_epoch().count());
    std::uniform_int_distribution<int> dist(1, terrain->size() - 2);

    for (int i = 0; i < 10; ++i) {
        auto tree = LSystem(1.25f, 15.0f, "FFFFFFFF[[A]FA]A", 6);
        tree.transform.model = glm::translate(terrain->position(dist(gen), dist(gen))) * glm::scale(glm::vec3(0.2f));
        scene.addChild(std::move(tree));
    }

    auto cam = std::make_unique<Camera>(width, height);
    auto flyControl = scene.addChild(FreeFlying(cam.get(),
                                                glm::translate(glm::vec3(0, 10, 20))));
    cameras[0] = flyControl->addChild(std::move(cam));
    cameraControls[0] = flyControl;

    cam = std::make_unique<Camera>(width, height);
    auto walker = scene.addChild(TerrainWalker(terrain, cam.get(), glm::vec3(0.0f, 2.0f, 0.0f)));
    auto mesh = Mesh::cube();
    mesh.material = NormalMaterial::singleton();
    mesh.transform.model = glm::translate(glm::vec3(0.0f, 0.2f, 0.0f)) * glm::scale(glm::vec3(0.2f, 0.2f, 0.2f));
    walker->foot->addChild(mesh);
    cameras[1] = walker->head->addChild(std::move(cam));
    cameraControls[1] = walker;
    cameraControls[1]->freeze = true;
}

void Window::resizeCallback(int width, int height) {
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
    GLContext::resizeCallback(width, height);
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

void Window::keyCallback(int key, int scancode, int action, int mods) {
    // Check for a key press.
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                // Close the window. This causes the program to also terminate.
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
            case GLFW_KEY_C:
                std::swap(cameras[0], cameras[1]);
                std::swap(cameraControls[0], cameraControls[1]);
                cameraControls[0]->freeze = false;
                cameraControls[1]->freeze = true;
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
