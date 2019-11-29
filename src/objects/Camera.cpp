#include "Camera.h"

Camera::Camera(const glm::mat4 &p, const glm::mat4 &t)
        : Node(t), projection(p) {
}

Camera::Camera(const glm::mat4 &p, std::shared_ptr<Transform> t)
        : Node(std::move(t)), projection(p) {
}

void Camera::update() {
    auto cam = worldTransform();
    view = glm::inverse(cam);
    eye = glm::vec3(cam[3]);
    Node::update();
}

std::unique_ptr<Node> Camera::copy() {
    auto ret = std::make_unique<Camera>(projection);
    doCopy(ret.get());
    return ret;
}

void Camera::doCopy(Camera *dup) {
    Node::doCopy(dup);
    dup->projection = projection;
}

glm::mat4 Camera::orientation(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) {
    auto z = glm::normalize(eye - center);
    auto x = glm::normalize(glm::cross(up, z));
    auto y = glm::normalize(glm::cross(z, x));
    return glm::mat4(x.x, x.y, x.z, 0,
                     y.x, y.y, y.z, 0,
                     z.x, z.y, z.z, 0,
                     eye.x, eye.y, eye.z, 1);
}
