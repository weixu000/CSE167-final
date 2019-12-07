#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <vector>

#include "Geometry.h"

class Shader;

class GLVertexArray;

class BezierCurve : public Geometry {
public:
    BezierCurve();

    void draw(const glm::mat4 &world, const Camera &camera) override;

    std::vector<glm::vec3> controlPoints;

    void upload();

    AABB boundingBox() const override { return bb; }

    glm::vec3 position(float t);

    glm::vec3 derivative(float t);

protected:
    NodePtr clone() override { return std::make_unique<BezierCurve>(*this); }

private:
    std::shared_ptr<GLVertexArray> vao;

    AABB bb;

    std::tuple<int, float> segment(float t);

    static std::unique_ptr<Shader> shader;

    static glm::mat4 B;
};


#endif //BEZIERCURVE_H
