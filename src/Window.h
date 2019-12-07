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
    Window();

    void loop();

    void initializeObjects();

    void update();

    void draw();

    void resizeCallback(int width, int height) override;

    void keyCallback(int key, int scancode, int action, int mods) override;

    void mouseButtonCallback(int button, int action, int mods) override;

    void cursorPosCallback(double x, double y) override;

private:
    Group scene;

    std::array<Camera *, 2> cameras;

    std::array<Group *, 2> cameraControls;
};

#endif
