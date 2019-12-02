#include "Group.h"

Group::Group(const Group &other) : Node(other) {
    for (auto &n:other.children) {
        children.push_back({n.ptr->clone(), false});
        children.back().ptr->_parent = this;
    }
}

Group::Group(Group &&other) noexcept {
    *this = std::move(other);
}

Group &Group::operator=(const Group &other) {
    *this = std::move(Group(other));
    return *this;
}

Group &Group::operator=(Group &&other) noexcept {
    children = std::move(other.children);
    for (auto &n:children) {
        n.ptr->_parent = this;
    }
    Node::operator=(std::move(other));
    return *this;
}

void Group::draw(const glm::mat4 &world, const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &eye) {
    auto m = world * transform.model;
    for (auto &n:children) {
        if (!n.culled) {
            n.ptr->draw(m, projection, view, eye);
        }
    }
}

void Group::update() {
    for (auto &n:children) {
        n.ptr->update();
    }
}

bool Group::cull(const glm::mat4 &view_proj) {
    auto m = view_proj * transform.model;
    auto culled = true;
    for (auto &n:children) {
        n.culled = n.ptr->cull(m);
        if (!n.culled) {
            culled = false;
        }
    }
    return culled;
}

