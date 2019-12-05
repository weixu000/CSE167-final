#ifndef TERRAIN_H
#define TERRAIN_H

#include "Mesh.h"

class Terrain : public Mesh {
public:
    Terrain(int n, const std::array<float, 4> &corners, float height_range);

    glm::vec3 position(float u, float v);

    glm::vec3 derivativeU(float u, float v);

    glm::vec3 derivativeV(float u, float v);

    size_t size() const { return heights.size(); }

protected:
    NodePtr clone() override { return std::make_unique<Terrain>(*this); }

private:
    using HeightMap = std::vector<std::vector<float>>;

    HeightMap heights;

    static HeightMap diamondSquare(int n, const std::array<float, 4> &corners, float height_range);

    std::tuple<float, float, glm::vec3, glm::vec3, glm::vec3, glm::vec3> patch(float u, float v);
};


#endif //TERRAIN_H
