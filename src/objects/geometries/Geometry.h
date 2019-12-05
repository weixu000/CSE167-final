#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include "../Node.h"

class AABB {
public:
    AABB() = default;

    AABB(const glm::vec3 &minVal, const glm::vec3 &maxVal);

    glm::vec3 min() const { return vertices[0]; }

    glm::vec3 max() const { return vertices[6]; }

    /*    y
     *    4----7
     *   /|   /|
     *  5-+--6 |
     *  | 0--+-3 x
     *  |/   |/
     *  1----2
     * z
     */
    std::array<glm::vec3, 8> vertices{};
};


class Geometry : public Node {
public:
    using Node::Node;

    void update() override {}

    virtual AABB boundingBox() const = 0;

    // Cull by the bounding box
    bool cull(const glm::mat4 &view_proj) override;
};

#endif

