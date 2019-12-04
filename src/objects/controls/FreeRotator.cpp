#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

#include "FreeRotator.h"
#include "../Camera.h"

void FreeRotator::rotate(const glm::vec2 &current) {
    auto delta = current - previous;
    delta.x *= glm::pi<float>() / camera->width;
    delta.y *= glm::pi<float>() / camera->height;

    eulerX = std::remainder(eulerX + delta.x, 2 * glm::pi<float>());
    eulerY = std::remainder(eulerY + delta.y, 2 * glm::pi<float>());
    auto rotation = glm::eulerAngleYX(eulerX, eulerY);
    transform.model = glm::translate(glm::vec3(transform.model[3])) * rotation;
    previous = current;
}

void FreeRotator::onMouseMove(float x, float y) {
    if (startedRotate) {
        rotate(glm::vec2(x, y));
    }
}

void FreeRotator::onMouseButtonPress(MouseButton button, int mods, float x, float y) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        startedRotate = true;
        previous = glm::vec2(x, y);
    }
    Group::onMouseButtonPress(button, mods, x, y);
}

void FreeRotator::onMouseButtonRelease(MouseButton button, int mods, float x, float y) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        startedRotate = false;
    }
    Group::onMouseButtonRelease(button, mods, x, y);
}

