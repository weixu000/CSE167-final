#ifndef COLORMAPMATERIAL_H
#define COLORMAPMATERIAL_H

#include "Material.h"
#include "../gl_wraps/Shader.h"
#include "../gl_wraps/Texture2D.h"

class ColormapMaterial : public Material {
public:
    explicit ColormapMaterial(std::shared_ptr<Texture2D> tex)
            : tex(std::move(tex)) {
        if (!shader) {
            shader = std::make_unique<Shader>("shaders/terrain.vert", "shaders/terrain.frag");
        }
    }

    Shader &setUp() const override {
        shader->use();

        // Use cube map
        glActiveTexture(GL_TEXTURE0);
        tex->bind();
        shader->setUniform("cubemap", 0);

        return *shader;
    }

    void tearDown() const override {
        tex->unbind();
    }

    std::shared_ptr<Texture2D> tex;

private:
    static inline std::unique_ptr<Shader> shader;
};


#endif //COLORMAPMATERIAL_H
