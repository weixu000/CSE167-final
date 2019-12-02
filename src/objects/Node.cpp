#include "Node.h"

Node::Node(const glm::mat4 &t)
        : transform(t) {
}

Node::Node(const Node &other)
        : transform(other.transform) {
}

Node::Node(Node &&other) noexcept {
    *this = std::move(other);
}

Node &Node::operator=(const Node &other) {
    _culled = false;
    _parent = nullptr;
    transform = other.transform;
    return *this;
}

Node &Node::operator=(Node &&other) noexcept {
    _culled = other._culled;
    other._culled = false;

    _parent = other._parent;
    other._parent = nullptr;

    transform = std::move(other.transform);
    return *this;
}

glm::mat4 Node::worldTransform() const {
    auto world = glm::mat4(1.0f);
    for (const Node *p = this; p != nullptr; p = p->parent()) {
        world = p->transform.model * world;
    }
    return world;
}
