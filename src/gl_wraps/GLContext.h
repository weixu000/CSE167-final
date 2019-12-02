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
};

#endif //OPENGLCONTEXT_H
