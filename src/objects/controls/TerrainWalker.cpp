#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

#include "TerrainWalker.h"
#include "../Camera.h"
#include "../../Time.h"
#include "FreeRotator.h"

TerrainWalker::TerrainWalker(Terrain *t, Camera *cam, float tall)
        : terrain(t) {
    foot = addChild(Group());
    head = addChild(FreeRotator(cam, glm::translate(glm::vec3(0.0f, tall, 0.0f))));
    set();
}

void TerrainWalker::update() {
    auto rotation = glm::mat3(head->transform.model);
    auto foward_vec = -rotation[2];
    auto left_vec = -rotation[0];
    auto movement = forward * foward_vec + left * left_vec;

    auto sensitivity = speed * Time::delta();
    auto du = glm::normalize(terrain->derivativeU(u, v));
    auto dv = glm::normalize(terrain->derivativeV(u, v));
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
    } else if (key == leftKey || key == rightKey) {
        left = 0.0f;
    }
    Group::onKeyRelease(key, mods);
}

void TerrainWalker::onMouseMove(float x, float y) {
    Group::onMouseMove(x, y);

    // use FreeRotator to update foot
    float euler_x, euler_y, euler_z;
    glm::extractEulerAngleYXZ(head->transform.model, euler_y, euler_x, euler_z);
    foot->transform.model = glm::eulerAngleY(euler_y);
}
