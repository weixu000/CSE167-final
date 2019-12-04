#ifndef SKYBOX_H
#define SKYBOX_H

#include "geometries/Mesh.h"

class TextureCubemap;

class Skybox : public Node {
public:
    Skybox();

    void draw(const glm::mat4 &world, const Camera &camera) override {
        // Inside the cube
        cube->draw(world, camera);
    }

    void update() override {}

    bool cull(const glm::mat4 &view_proj) override { return false; }

    static inline std::shared_ptr<TextureCubemap> cubemap;

protected:
    NodePtr clone() override { return std::make_unique<Skybox>(*this); }

private:
    static inline std::shared_ptr<Mesh> cube;
};


#endif //SKYBOX_H
