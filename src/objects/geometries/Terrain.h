#ifndef TERRAIN_H
#define TERRAIN_H

#include "Wireframe.h"
#include "../../gl_wraps/Shader.h"
#include "../../gl_wraps/Texture2D.h"

class Terrain : public Wireframe {
public:
    Terrain(int n, const std::array<float, 4> &corners, float height_range);

    void draw(const glm::mat4 &world, const Camera &camera) override;

protected:
    NodePtr clone() override { return std::make_unique<Terrain>(*this); }

private:
    using HeightMap = std::vector<std::vector<float>>;

    static HeightMap diamondSquare(int n, const std::array<float, 4> &corners, float height_range);

    std::shared_ptr<Texture2D> tex;

    static std::unique_ptr<Shader> shader;
};


#endif //TERRAIN_H
