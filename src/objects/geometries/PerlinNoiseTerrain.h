#ifndef PERLINNOISETERRAIN_H
#define PERLINNOISETERRAIN_H

#include "Mesh.h"
#include "ParametricSurface.h"

class PerlinNoiseTerrain : public Mesh, public ParametricSurface {
public:
    PerlinNoiseTerrain(int n, int tessellation);

    glm::vec3 position(float u, float v) override { return transform.model * glm::vec4(u, perlin(u, v), v, 1.0f); }

    glm::vec3 derivativeU(float u, float v) override {
        return glm::mat3(transform.model) * glm::vec3(1, perlinX(u, v), 0);
    }

    glm::vec3 derivativeV(float u, float v) override {
        return glm::mat3(transform.model) * glm::vec3(0, perlinY(u, v), 1);
    }

    int size() const override { return gradients.size(); }

protected:
    NodePtr clone() override { return std::make_unique<PerlinNoiseTerrain>(*this); }

private:
    using HeightMap = std::vector<std::vector<float>>;

    std::vector<std::vector<glm::vec2>> gradients;

    std::tuple<float, float, glm::vec2, glm::vec2, glm::vec2, glm::vec2> grid(float x, float y);

    float perlin(float x, float y);

    float perlinX(float x, float y);

    float perlinY(float x, float y);
};


#endif //PERLINNOISETERRAIN_H
