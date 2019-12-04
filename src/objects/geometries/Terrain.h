#ifndef TERRAIN_H
#define TERRAIN_H

#include "Wireframe.h"
#include "../../materials/ColormapMaterial.h"

class Terrain : public Wireframe {
public:
    Terrain(int n, const std::array<float, 4> &corners, float height_range);

    void draw(const glm::mat4 &world, const Camera &camera) override;

    glm::vec3 position(float u, float v);

    glm::vec3 derivativeU(float u, float v);

    glm::vec3 derivativeV(float u, float v);

    using HeightMap = std::vector<std::vector<float>>;

    HeightMap heights;

protected:
    NodePtr clone() override { return std::make_unique<Terrain>(*this); }

private:
    static HeightMap diamondSquare(int n, const std::array<float, 4> &corners, float height_range);

    static inline std::unique_ptr<ColormapMaterial> material;

    std::tuple<float, float, glm::vec3, glm::vec3, glm::vec3, glm::vec3> patch(float u, float v);
};


#endif //TERRAIN_H
