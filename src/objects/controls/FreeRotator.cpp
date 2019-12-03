#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

#include "FreeRotator.h"

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

glm::vec3 FreeRotator::windowCoordToCamDir(float x, float y, int width, int height, const glm::mat4 &proj) {
    auto viewport = glm::vec4(0.0f, 0.0f, width, height);
    auto win_coord = glm::vec3(x, height - 1 - y, 0);
    return glm::normalize(glm::unProject(win_coord, glm::mat4(1.0f), proj, viewport));
}

