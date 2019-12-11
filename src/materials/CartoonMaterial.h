#ifndef CARTOONMATERIAL_H
#define CARTOONMATERIAL_H

#include "Material.h"
#include "../gl_wraps/Shader.h"
#include "../gl_wraps/Texture2D.h"

class CartoonMaterial : public Material {
public:
    CartoonMaterial() {
        if (!shader) {
            shader = std::make_unique<Shader>("shaders/heightmap.vert", "shaders/cartoon.frag");
        }
    }

    Shader &setUp() const override {
        shader->use();

        glActiveTexture(GL_TEXTURE0);
        tex->bind();
        shader->setUniform("colormap", 0);
        shader->setUniform("minHeight", minHeight);
        shader->setUniform("maxHeight", maxHeight);

        return *shader;
    }

    std::shared_ptr<Texture2D> tex;

    float minHeight, maxHeight;

    void tearDown() const override {
        tex->unbind();
    }

private:
    static inline std::unique_ptr<Shader> shader;
};


#endif //CARTOONMATERIAL_H
