#ifndef MESH_H
#define MESH_H

#include "../../gl_wraps/gl.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <string>

#include "Geometry.h"
#include "../../gl_wraps/Shader.h"
#include "../../gl_wraps/GLBuffer.h"
#include "../../gl_wraps/GLVertexArray.h"
#include "../../materials/Material.h"

class Mesh : public Geometry {
public:
    Mesh() = default;

    Mesh(const std::vector<glm::vec3> &attrs, const std::vector<GLuint> &indices);

    static Mesh fromObjFile(const std::string &objFilename);

    static Mesh cube();

    void draw(const glm::mat4 &world, const Camera &camera) override;

    AABB boundingBox() const override { return bb; }

    std::shared_ptr<Material> material;

protected:
    NodePtr clone() override { return std::make_unique<Mesh>(*this); }

private:
    GLsizei count = 0;
    std::shared_ptr<GLVertexArray> vao = std::make_shared<GLVertexArray>();
    std::shared_ptr<GLBuffer> vbo = std::make_shared<GLBuffer>(), ebo = std::make_shared<GLBuffer>();

    AABB bb;
};


#endif //MESH_H
