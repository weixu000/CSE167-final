#ifndef WIREFRAME_H
#define WIREFRAME_H

#include "../../gl_wraps/gl.h"

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "Geometry.h"
#include "../../gl_wraps/GLBuffer.h"
#include "../../gl_wraps/GLVertexArray.h"
#include "../../materials/Material.h"


class Wireframe : public Geometry {
public:
    Wireframe() = default;

    explicit Wireframe(const std::vector<glm::vec3> &vertices, const std::vector<GLuint> &indices);

    void upload(const std::vector<glm::vec3> &vertices, const std::vector<GLuint> &indices);

    static Wireframe fromAABB(const AABB &bb);

    void draw(const glm::mat4 &world, const Camera &camera) override;

    AABB boundingBox() const override { return bb; }

    std::shared_ptr<Material> material;

protected:
    NodePtr clone() override { return std::make_unique<Wireframe>(*this); }

    GLsizei count = 0;
    std::shared_ptr<GLVertexArray> vao = std::make_shared<GLVertexArray>();
    std::shared_ptr<GLBuffer> vbo = std::make_shared<GLBuffer>(), ebo = std::make_shared<GLBuffer>();

    AABB bb;
};


#endif //WIREFRAME_H
