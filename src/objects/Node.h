#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>
#include <memory>
#include <list>

#include "Transform.h"

class Node {
public:
    explicit Node(const glm::mat4 &t = glm::mat4(1.0f));

    Node(const Node &);

    Node &operator=(const Node &);

    Node(Node &&) noexcept;

    Node &operator=(Node &&) noexcept;

    virtual ~Node() = default;

    virtual void draw(const glm::mat4 &world, const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &eye);

    virtual void update();

    virtual bool cull(const glm::mat4 &view_proj);

    bool culled() const { return _culled; }

    glm::mat4 worldTransform() const;

    template<typename T>
    T *addChild(std::unique_ptr<T> child) {
        assert(!child->_parent);
        child->_parent = this;
        children.push_back(std::move(child));
        return static_cast<T *>(children.back().get());
    }

    template<typename T>
    std::remove_reference_t<T> *addChild(T &&child) {
        return addChild(std::make_unique<std::remove_reference_t<T>>(std::forward<T>(child)));
    }

    Node *parent() const { return _parent; }

    Transform transform;

protected:
    bool _culled = false;

    Node *_parent = nullptr;

    using NodePtr = std::unique_ptr<Node>;

    std::list<NodePtr> children;

    // Enable deep copy of unkown type of node
    // Every concrete inherited class must implement this
    virtual NodePtr clone() { return std::make_unique<Node>(*this); }
};


#endif //NODE_H
