#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

#include "FreeRotator.h"
#include "../Camera.h"

void FreeRotator::startRotate(const glm::vec3 &dir) {
    startedRotate = true;
    initial = dir;
}

void FreeRotator::stopRotate() {
    startedRotate = false;
}

void FreeRotator::rotate(const glm::vec3 &dir) {
    if (startedRotate) {
        auto dot = glm::clamp(glm::dot(initial, dir), -1.0f, 1.0f);
        auto rad = -glm::acos(dot);
        auto axis = glm::cross(initial, dir);
        if (glm::length(axis) == 0) {
            return;
        }
        auto rot = glm::rotate(rad, axis);
        transform.model = transform.model * rot;
        initial = dir;
    }
}

glm::vec3 FreeRotator::windowCoordToCamDir(float x, float y) {
    auto viewport = glm::vec4(0.0f, 0.0f, camera->width, camera->height);
    auto win_coord = glm::vec3(x, camera->height - 1 - y, 0);
    return glm::normalize(glm::unProject(win_coord, glm::mat4(1.0f), camera->projection, viewport));
}

void FreeRotator::onMouseMove(float x, float y) {
    rotate(windowCoordToCamDir(x, y));
}

void FreeRotator::onMouseButtonPress(MouseButton button, int mods, float x, float y) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        startRotate(windowCoordToCamDir(x, y));
    }
    Group::onMouseButtonPress(button, mods, 0, 0);
}

void FreeRotator::onMouseButtonRelease(MouseButton button, int mods, float x, float y) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        stopRotate();
    }

    Group::onMouseButtonRelease(button, mods, 0, 0);
}

