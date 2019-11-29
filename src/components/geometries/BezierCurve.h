#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include "Geometry.h"
#include "../../gl_wraps/Shader.h"
#include "../../gl_wraps/GLBuffer.h"
#include "../../gl_wraps/GLVertexArray.h"

class BezierCurve : public Geometry {
public:
    BezierCurve();

    void
    draw(const glm::mat4 &world, const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &eye) override;

    std::vector<glm::vec3> controlPoints;

    void upload();

    AABB boundingBox() const override { return bb; }

    glm::vec3 position(float t);

    glm::vec3 derivative(float t);

private:
    std::shared_ptr<GLVertexArray> vao = std::make_shared<GLVertexArray>();
    std::shared_ptr<GLBuffer> vbo = std::make_shared<GLBuffer>(), ebo = std::make_shared<GLBuffer>();

    AABB bb;

    std::tuple<int, float> segment(float t);

    static std::unique_ptr<Shader> shader;

    static glm::mat4 B;
};


#endif //BEZIERCURVE_H
