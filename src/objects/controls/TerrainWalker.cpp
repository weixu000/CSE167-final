#include <glm/gtx/transform.hpp>

#include "TerrainWalker.h"
#include "../../Time.h"

TerrainWalker::TerrainWalker(Terrain *t)
        : terrain(t) {
    set();
}

void TerrainWalker::update() {
    auto sensitivity = speed * Time::delta();

    auto du = glm::normalize(terrain->derivativeU(u, v));
    auto dv = glm::normalize(terrain->derivativeV(u, v));
    auto movement = forward * -glm::vec3(transform.model[2]) + left * -glm::vec3(transform.model[0]);

    u += glm::dot(sensitivity * movement, du);
    v += glm::dot(sensitivity * movement, dv);

    set();
    Group::update();
}

void TerrainWalker::set() {
    u = std::max(0.0f, std::min(u, float(terrain->heights.size())));
    v = std::max(0.0f, std::min(v, float(terrain->heights.size())));
    transform.model = glm::translate(terrain->position(u, v));
}

void TerrainWalker::onKeyPress(Key key, int mods) {
    if (key == forwardKey) {
        forward = 1.0f;
    } else if (key == leftKey) {
        left = 1.0f;
    } else if (key == backwardKey) {
        forward = -1.0f;
    } else if (key == rightKey) {
        left = -1.0f;
    }
    Group::onKeyPress(key, mods);
}

void TerrainWalker::onKeyRelease(int key, int mods) {
    if (key == forwardKey || key == backwardKey) {
        forward = 0.0f;
    } else if (key == leftKey || key == backwardKey) {
        left = 0.0f;
    }
    Group::onKeyRelease(key, mods);
}
