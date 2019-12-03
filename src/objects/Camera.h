#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtx/transform.hpp>

#include "Node.h"

class Shader;

class Camera : public Node {
public:
    glm::mat4 projection, view;
    glm::vec3 eye;
    float width, height;
    float zNear = 0.1f, zFar = 1000.0f;
    float fovy = 60.f;

    explicit Camera(float w, float h, const glm::mat4 &t = glm::mat4(1.0f));

    void draw(const glm::mat4 &, const Camera &) override {}

    void update() override;

    bool cull(const glm::mat4 &) override { return true; }

    void setUniform(Shader &shader) const;

    void resize(float w, float h) {
        width = w;
        height = h;
        projection = glm::perspective(glm::radians(fovy),
                                      width / height,
                                      zNear, zFar);
    }

    // Camera matrix, inverse of view matrix glm::lookAt
    static glm::mat4 orientation(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);

protected:
    NodePtr clone() override { return std::make_unique<Camera>(*this); }
};


#endif //CAMERA_H
