#ifndef GROUP_H
#define GROUP_H

#include "Node.h"

class Group : public Node {
public:
    using Node::Node;

    Group(const Group &);

    Group &operator=(const Group &);

    Group(Group &&) noexcept;

    Group &operator=(Group &&) noexcept;

    void draw(const glm::mat4 &world, const Camera &camera) override;

    void update() override;

    bool cull(const glm::mat4 &view_proj) override;

    void onKeyPress(Key key, int mods) override;

    void onKeyRelease(int key, int mods) override;

    void onMouseMove(float x, float y) override;

    void onMouseButtonPress(MouseButton button, int mods, float x, float y) override;

    void onMouseButtonRelease(MouseButton button, int mods, float x, float y) override;

    template<typename T>
    T *addChild(std::unique_ptr<T> child) {
        assert(!child->_parent);
        child->_parent = this;
        auto ret = child.get();
        children.push_back({std::move(child), false});
        return ret;
    }

    template<typename T>
    std::remove_reference_t<T> *addChild(T &&child) {
        return addChild(std::make_unique<std::remove_reference_t<T>>(std::forward<T>(child)));
    }

protected:
    NodePtr clone() override { return std::make_unique<Group>(*this); }

private:
    struct CullingNodePtr {
        NodePtr ptr;
        bool culled;
    };
    std::list<CullingNodePtr> children;
};


#endif //GROUP_H
