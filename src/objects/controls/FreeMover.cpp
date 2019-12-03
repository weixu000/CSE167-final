#include <glm/gtx/transform.hpp>

#include "FreeMover.h"
#include "../../Time.h"

void FreeMover::update() {
    const auto sensitivity = 10.0f * Time::delta();
    auto movement = glm::vec3(0.0f);
    if (forward) {
        movement += sensitivity * -glm::vec3(transform.model[2]);
    } else if (backward) {
        movement += sensitivity * glm::vec3(transform.model[2]);
    }
    if (left) {
        movement += sensitivity * -glm::vec3(transform.model[0]);
    } else if (right) {
        movement += sensitivity * glm::vec3(transform.model[0]);
    }
    if (up) {
        movement += sensitivity * glm::vec3(transform.model[1]);
    } else if (down) {
        movement += sensitivity * -glm::vec3(transform.model[1]);
    }
    transform.model = glm::translate(movement) * transform.model;

    Group::update();
}

void FreeMover::onKeyPress(Key key, int mods) {
    if (key == forwardKey) {
        forward = true;
    } else if (key == leftKey) {
        left = true;
    } else if (key == backwardKey) {
        backward = true;
    } else if (key == rightKey) {
        right = true;
    } else if (key == upKey) {
        up = true;
    } else if (key == downKey) {
        down = true;
    }

    Group::onKeyPress(key, mods);
}

void FreeMover::onKeyRelease(int key, int mods) {
    if (key == forwardKey) {
        forward = false;
    } else if (key == leftKey) {
        left = false;
    } else if (key == backwardKey) {
        backward = false;
    } else if (key == rightKey) {
        right = false;
    } else if (key == upKey) {
        up = false;
    } else if (key == downKey) {
        down = false;
    }

    Group::onKeyRelease(key, mods);
}
