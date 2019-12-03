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

void Group::draw(const glm::mat4 &world, const Camera &camera) {
    auto m = world * transform.model;
    for (auto &n:children) {
        if (!n.culled) {
            n.ptr->draw(m, camera);
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

void Group::onKeyPress(Key key, int mods) {
    for (auto &n:children) {
        n.ptr->onKeyPress(key, mods);
    }
}

void Group::onKeyRelease(int key, int mods) {
    for (auto &n:children) {
        n.ptr->onKeyRelease(key, mods);
    }
}

void Group::onMouseMove(float x, float y) {
    for (auto &n:children) {
        n.ptr->onMouseMove(x, y);
    }
}

void Group::onMouseButtonPress(MouseButton button, int mods, float x, float y) {
    for (auto &n:children) {
        n.ptr->onMouseButtonPress(button, mods, x, y);
    }
}

void Group::onMouseButtonRelease(MouseButton button, int mods, float x, float y) {
    for (auto &n:children) {
        n.ptr->onMouseButtonRelease(button, mods, x, y);
    }
}

