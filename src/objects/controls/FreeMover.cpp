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
