#ifndef SKYBOXMATERIAL_H
#define SKYBOXMATERIAL_H

#include "Material.h"
#include "../gl_wraps/TextureCubemap.h"
#include "../gl_wraps/Shader.h"

class SkyboxMaterial : public Material {
public:
    explicit SkyboxMaterial(std::shared_ptr<TextureCubemap> cubemap)
            : cubemap(std::move(cubemap)) {
        if (!shader) {
            shader = std::make_unique<Shader>("shaders/skybox.vert", "shaders/skybox.frag");
        }
    }

    Shader &setUp() const override {
        shader->use();

        // Use cube map
        glActiveTexture(GL_TEXTURE0);
        cubemap->bind();
        shader->setUniform("cubemap", 0);

        glCullFace(GL_FRONT);

        return *shader;
    }

    void tearDown() const override {
        glCullFace(GL_BACK);
        cubemap->unbind();
    }

    std::shared_ptr<TextureCubemap> cubemap;

private:
    static inline std::unique_ptr<Shader> shader;
};


#endif //SKYBOXMATERIAL_H
