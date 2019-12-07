#ifndef CAMERA_H
#define CAMERA_H

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

    void resize(float w, float h);

protected:
    NodePtr clone() override { return std::make_unique<Camera>(*this); }
};


#endif //CAMERA_H
