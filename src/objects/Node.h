#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>
#include <memory>
#include <list>

#include "Transform.h"
#include "../Input.h"

class Camera;

class Node {
public:
    explicit Node(const glm::mat4 &t = glm::mat4(1.0f));

    virtual ~Node() = default;

    Node(const Node &);

    Node &operator=(const Node &);

    Node(Node &&) noexcept;

    Node &operator=(Node &&) noexcept;

    virtual void draw(const glm::mat4 &world, const Camera &camera) = 0;

    virtual void update() = 0;

    virtual bool cull(const glm::mat4 &view_proj) = 0;

    glm::mat4 worldTransform() const;

    Node *parent() const { return _parent; }

    Transform transform;

    virtual void onKeyPress(Key key, int mods) {}

    virtual void OnKeyRelease(int key, int mods) {}

protected:
    using NodePtr = std::unique_ptr<Node>;

    // Enable deep copy of unkown type of node
    // Every concrete inherited class must implement this
    virtual NodePtr clone() = 0;

private:
    Node *_parent = nullptr; // maintained by Group

    friend class Group;
};


#endif //NODE_H
