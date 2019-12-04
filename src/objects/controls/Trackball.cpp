#include <glm/gtx/transform.hpp>

#include "Trackball.h"
#include "../Camera.h"

void Trackball::start(float x, float y) {
    initial = viewportToTrackball(x, y);
    started = true;
}

void Trackball::move(float x, float y) {
    if (started) {
        auto cur = viewportToTrackball(x, y);
        auto rad = glm::acos(glm::dot(initial, cur));
        auto axis = glm::cross(initial, cur);
        if (glm::length(axis) == 0) {
            return;
        }
        auto next = glm::rotate(rad, axis);
        auto delta = next * glm::transpose(orientation);
        orientation = next;
        transform.model = delta * transform.model;
    }
}

void Trackball::stop() {
    started = false;
    orientation = glm::mat4(1.0f);
}

void Trackball::scale(float offset) {
    transform.model = glm::scale(glm::vec3(glm::max(0.0f, 1 + 0.1f * offset))) * transform.model;
}

glm::vec3 Trackball::viewportToTrackball(float x, float y) {
    glm::vec3 ret(2 * x - 1,
                  -(2 * y - 1),
                  0.0f);
    auto z2 = 1 - ret.x * ret.x - ret.y * ret.y;
    if (z2 >= 0) {
        ret.z = glm::sqrt(z2);
        return ret;
    } else {
        return glm::normalize(ret);
    }
}

void Trackball::onMouseMove(float x, float y) {
    move(x / camera->width, y / camera->height);
    Group::onMouseMove(x, y);
}

void Trackball::onMouseButtonPress(MouseButton button, int mods, float x, float y) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        start(x / camera->width, y / camera->height);
    }
    Group::onMouseButtonPress(button, mods, x, y);
}

void Trackball::onMouseButtonRelease(MouseButton button, int mods, float x, float y) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        stop();
    }
    Group::onMouseButtonRelease(button, mods, x, y);
}
