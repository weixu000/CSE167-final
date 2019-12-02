#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtx/transform.hpp>

#include "Node.h"

class Camera : public Node {
public:
    glm::mat4 projection, view;
    glm::vec3 eye;

    explicit Camera(const glm::mat4 &p, const glm::mat4 &t = glm::mat4(1.0f));

    void draw(const glm::mat4 &, const glm::mat4 &, const glm::mat4 &, const glm::vec3 &) override {}

    void update() override;

    bool cull(const glm::mat4 &view_proj) override {
        _culled = true;
        return _culled;
    }

    // Camera matrix, inverse of view matrix glm::lookAt
    static glm::mat4 orientation(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);

protected:
    NodePtr clone() override { return std::make_unique<Camera>(*this); }
};


#endif //CAMERA_H
