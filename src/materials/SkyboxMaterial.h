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
            foggyShader = std::make_unique<Shader>("shaders/skybox.vert", "shaders/skybox_fog.frag");
        }
    }

    Shader &setUp() const override {
        Shader *s = foggy ? foggyShader.get() : shader.get();
        s->use();

        // Use cube map
        glActiveTexture(GL_TEXTURE0);
        cubemap->bind();
        s->setUniform("cubemap", 0);

        glCullFace(GL_FRONT);

        return *s;
    }

    void tearDown() const override {
        glCullFace(GL_BACK);
        cubemap->unbind();
    }

    std::shared_ptr<TextureCubemap> cubemap;

    bool foggy = false;

private:
    static inline std::unique_ptr<Shader> shader, foggyShader;
};


#endif //SKYBOXMATERIAL_H
