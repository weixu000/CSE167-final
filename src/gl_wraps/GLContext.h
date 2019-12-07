#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

#include "gl.h"
#include <GLFW/glfw3.h>

// Make sure OpenGL context is ready before anything else, since it is base class
class GLContext {
public:
    GLFWwindow *window;

    int width = 640, height = 480;

    GLContext();

    virtual ~GLContext();

    GLContext(const GLContext &) = delete;

    GLContext(GLContext &&) = delete;

    GLContext &operator=(const GLContext &) = delete;

    GLContext &operator=(GLContext &&) = delete;

    static GLContext *retrieve(GLFWwindow *w) { return reinterpret_cast<GLContext *>(glfwGetWindowUserPointer(w)); }

    virtual void resizeCallback(int width, int height);

    virtual void keyCallback(int key, int scancode, int action, int mods) {}

    virtual void mouseButtonCallback(int button, int action, int mods) {}

    virtual void cursorPosCallback(double x, double y) {}

    virtual void scrollCallback(double xoffset, double yoffset) {}

private:
    void setupCallbacks();
};

#endif //OPENGLCONTEXT_H
