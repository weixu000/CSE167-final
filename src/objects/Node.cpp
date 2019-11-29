#include "Node.h"

Node::Node(std::shared_ptr<Transform> t)
        : transform(std::move(t)) {
}

Node::Node(const glm::mat4 &t)
        : transform(std::make_shared<Transform>(t)) {

}

void Node::draw(const glm::mat4 &world, const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &eye) {
    auto m = world * transform->model;
    for (auto &n:children) {
        if (!n->culled()) {
            n->draw(m, projection, view, eye);
        }
    }
}

void Node::update() {
    for (auto &n:children) {
        n->update();
    }
}

bool Node::cull(const glm::mat4 &view_proj) {
    auto m = view_proj * transform->model;
    size_t num_culled = 0;

    for (auto &n:children) {
        if (n->cull(m)) {
            ++num_culled;
        }
    }
    _culled = num_culled == children.size();
    return _culled;
}

glm::mat4 Node::worldTransform() const {
    auto world = glm::mat4(1.0f);
    for (const Node *p = this; p != nullptr; p = p->parent()) {
        world = p->transform->model * world;
    }
    return world;
}

Node *Node::addChild(NodePtr child) {
    assert(!child->_parent);
    child->_parent = this;
    children.push_back(std::move(child));
    return children.back().get();
}

Node::Node(const Node &other) : transform(other.transform) {
    for (auto &n:other.children) {
        children.push_back(n->clone());
    }
}

Node &Node::operator=(const Node &other) {
    *this = std::move(Node(other));
    return *this;
}
