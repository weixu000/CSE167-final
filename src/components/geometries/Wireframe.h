#ifndef WIREFRAME_H
#define WIREFRAME_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else

#include <GL/glew.h>

#endif

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "Geometry.h"
#include "../../gl_wraps/GLBuffer.h"
#include "../../gl_wraps/GLVertexArray.h"


class Wireframe : public Geometry {
public:
    explicit Wireframe(const std::vector<glm::vec3> &vertices, const std::vector<GLuint> &indices);

    static Wireframe fromAABB(const AABB &bb);

    void
    draw(const glm::mat4 &world, const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &eye) override;

    AABB boundingBox() const override { return bb; }

private:
    GLsizei count = 0;
    std::shared_ptr<GLVertexArray> vao = std::make_shared<GLVertexArray>();
    std::shared_ptr<GLBuffer> vbo = std::make_shared<GLBuffer>(), ebo = std::make_shared<GLBuffer>();

    AABB bb;
};


#endif //WIREFRAME_H
