#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "gl_wraps/gl.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "objects/Group.h"
#include "objects/Camera.h"
#include "objects/geometries/Skybox.h"
#include "gl_wraps/GLContext.h"

class Window : public GLContext {
public:
    Group scene;

    std::array<Camera *, 2> cameras;

    std::array<Group *, 2> cameraControls;

    static Window *retrieve(GLFWwindow *w) { return reinterpret_cast<Window *>(glfwGetWindowUserPointer(w)); }

    Window();

    void loop();

    void setupCallbacks();

    void initializeObjects();

    void resizeCallback(int width, int height);

    void update();

    void draw();

    void keyCallback(int key, int scancode, int action, int mods);

    void mouseButtonCallback(int button, int action, int mods);

    void cursorPosCallback(double x, double y);

    void scrollCallback(double xoffset, double yoffset);
};

#endif
