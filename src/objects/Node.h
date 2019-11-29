#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>
#include <memory>
#include <list>

#include "../components/Component.h"
#include "Transform.h"

class Node {
public:
    explicit Node(const glm::mat4 &t = glm::mat4(1.0f));

    explicit Node(std::shared_ptr<Transform> t);

    Node(const Node &);

    Node &operator=(const Node &);

    Node(Node &&) = default;

    Node &operator=(Node &&) = default;

    virtual ~Node() = default;

    virtual void draw(const glm::mat4 &world, const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &eye);

    virtual void update();

    virtual bool cull(const glm::mat4 &view_proj);

    bool culled() const { return _culled; }

    glm::mat4 worldTransform() const;

    using NodePtr = std::unique_ptr<Node>;

    Node *addChild(NodePtr child);

    Node *parent() const { return _parent; }

    std::shared_ptr<Transform> transform;

protected:
    bool _culled = false;

    Node *_parent = nullptr;

    std::list<NodePtr> children;

    // Enable deep copy of unkown type of node
    // Every concrete inherited class must implement this
    virtual NodePtr clone() { return std::make_unique<Node>(*this); }
};


#endif //NODE_H
