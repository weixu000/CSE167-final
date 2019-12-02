#ifndef SKYBOX_H
#define SKYBOX_H

#include "geometries/Mesh.h"
#include "../gl_wraps/TextureCubemap.h"

class Skybox : public Node {
public:
    Skybox();

    void
    draw(const glm::mat4 &world, const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &eye) override;

    void update() override {}

    bool cull(const glm::mat4 &view_proj) override { return false; }

protected:
    NodePtr clone() override { return std::make_unique<Skybox>(*this); }

private:
    std::shared_ptr<Mesh> cube;

    std::shared_ptr<Shader> shader;

    std::shared_ptr<TextureCubemap> cubemap;
};


#endif //SKYBOX_H
