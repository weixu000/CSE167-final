#ifndef SKYBOX_H
#define SKYBOX_H

#include "../components/geometries/Mesh.h"
#include "../gl_wraps/GLTexture.h"

class Skybox {
public:
    Skybox();

    void
    draw(const glm::mat4 &world, const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &eye);

    GLTexture cubeMap;

private:
    std::shared_ptr<Mesh> cube;

    std::shared_ptr<Shader> shader;
};


#endif //SKYBOX_H
