#include <glm/gtx/transform.hpp>

#include "Camera.h"
#include "../gl_wraps/Shader.h"

Camera::Camera(float w, float h, const glm::mat4 &t)
        : Node(t) {
    resize(w, h);
}

void Camera::update() {
    auto cam = worldTransform();
    view = glm::inverse(cam);
    eye = glm::vec3(cam[3]);
}

void Camera::setUniform(Shader &shader) const {
    shader.setUniform("projection", projection);
    shader.setUniform("view", view);
    shader.setUniform("eye", eye);
}

void Camera::resize(float w, float h) {
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(fovy),
                                  width / height,
                                  zNear, zFar);
}
