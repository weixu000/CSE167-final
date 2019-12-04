#ifndef TERRAINWALKER_H
#define TERRAINWALKER_H

#include "../Group.h"
#include "../geometries/Terrain.h"

class TerrainWalker : public Group {
public:
    explicit TerrainWalker(Terrain *t);

    void update() override;

    void onKeyPress(Key key, int mods) override;

    void onKeyRelease(int key, int mods) override;

    Key forwardKey = GLFW_KEY_W, backwardKey = GLFW_KEY_S,
            leftKey = GLFW_KEY_A, rightKey = GLFW_KEY_D;

protected:
    NodePtr clone() override { return std::make_unique<TerrainWalker>(*this); }

private:
    Terrain *terrain;

    void set();

    const float speed = 5.0f;

    float u = 0.0f, v = 0.0f;

    float forward = 0.0f, left = 0.0f;
};


#endif //TERRAINWALKER_H
