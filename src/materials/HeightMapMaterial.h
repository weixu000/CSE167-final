#ifndef COLORMAPMATERIAL_H
#define COLORMAPMATERIAL_H

#include "Material.h"
#include "../gl_wraps/Shader.h"
#include "../gl_wraps/Texture2D.h"

class HeightMapMaterial : public Material {
public:
    HeightMapMaterial() {
        if (!shader) {
            shader = std::make_unique<Shader>("shaders/heightmap.vert", "shaders/heightmap.frag");
        }
    }

    Shader &setUp() const override {
        shader->use();

        // Use cube map
        glActiveTexture(GL_TEXTURE0);
        tex->bind();
        shader->setUniform("cubemap", 0);
        shader->setUniform("minHeight", minHeight);
        shader->setUniform("maxHeight", maxHeight);

        return *shader;
    }

    void tearDown() const override {
        tex->unbind();
    }

    std::shared_ptr<Texture2D> tex;

    float minHeight, maxHeight;

private:
    static inline std::unique_ptr<Shader> shader;
};


#endif //COLORMAPMATERIAL_H
