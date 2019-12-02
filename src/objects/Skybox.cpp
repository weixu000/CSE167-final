#include "../../deps/stb_image/stb_image.h"

#include "Skybox.h"
#include "Camera.h"

Skybox::Skybox() {
    cube = std::make_shared<Mesh>(Mesh::cube());
    shader = std::make_shared<Shader>("shaders/skybox.vert", "shaders/skybox.frag");
    cube->useShader(shader);

    cubemap = std::make_shared<TextureCubemap>();
    cubemap->bind();
    cubemap->upload({
                            "textures/Skybox_Water222_right.jpg",
                            "textures/Skybox_Water222_left.jpg",
                            "textures/Skybox_Water222_top.jpg",
                            "textures/Skybox_Water222_base.jpg",
                            "textures/Skybox_Water222_front.jpg",
                            "textures/Skybox_Water222_back.jpg"
                    });

    // Use bilinear interpolation:
    cubemap->setFilter(GL_LINEAR, GL_LINEAR);

    // Use clamp to edge to hide skybox edges:
    cubemap->setWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

    cubemap->unbind();
}

void Skybox::draw(const glm::mat4 &world, const Camera &camera) {
    auto m = world * transform.model;

    // Use cube map
    glActiveTexture(GL_TEXTURE0);
    cubemap->bind();

    // Inside the cube
    glCullFace(GL_FRONT);
    shader->use();
    shader->setUniform("cubemap", 0);
    cube->draw(world, camera);
    glCullFace(GL_BACK);

    cubemap->unbind();
}
