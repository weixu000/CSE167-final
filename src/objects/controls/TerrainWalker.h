#ifndef TERRAINWALKER_H
#define TERRAINWALKER_H

#include "../Group.h"

class Camera;

class Terrain;

class TerrainWalker : public Group {
public:
    explicit TerrainWalker(Terrain *t, Camera *cam, const glm::vec3 &body);

    void update() override;

    void onKeyPress(Key key, int mods) override;

    void onKeyRelease(int key, int mods) override;

    void onMouseMove(float x, float y) override;

    Key forwardKey = GLFW_KEY_W, backwardKey = GLFW_KEY_S,
            leftKey = GLFW_KEY_A, rightKey = GLFW_KEY_D;

    // transform.model stores translation on the terrain
    // foot has Y rotation
    // head has X,Y rotation and Z translation
    Group *foot, *head;

protected:
    NodePtr clone() override { return std::make_unique<TerrainWalker>(*this); }

private:
    Terrain *terrain;

    void set();

    const float speed = 5.0f;

    float u = 0.0f, v = 0.0f;

    float forward = 0.0f, left = 0.0f;

    glm::vec3 body;
};


#endif //TERRAINWALKER_H
