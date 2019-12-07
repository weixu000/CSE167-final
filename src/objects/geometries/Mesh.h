#ifndef MESH_H
#define MESH_H

#include "../../gl_wraps/gl.h"

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "Geometry.h"

class Material;

class GLVertexArray;

class Mesh : public Geometry {
public:
    Mesh() = default;

    Mesh(const std::vector<glm::vec3> &attrs, const std::vector<GLuint> &indices);

    static Mesh fromObjFile(const std::string &objFilename);

    static Mesh faceNormalMesh(const std::vector<glm::vec3> &vertices, const std::vector<GLuint> &indices);

    static Mesh fromAABB(const AABB &bb);

    static Mesh cube();

    void draw(const glm::mat4 &world, const Camera &camera) override;

    AABB boundingBox() const override { return bb; }

    std::shared_ptr<Material> material;

protected:
    NodePtr clone() override { return std::make_unique<Mesh>(*this); }

    GLsizei count = 0;
    std::shared_ptr<GLVertexArray> vao;

    AABB bb;
};


#endif //MESH_H
