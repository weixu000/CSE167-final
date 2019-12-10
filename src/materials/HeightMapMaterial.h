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
            foggyShader = std::make_unique<Shader>("shaders/heightmap_fog.vert", "shaders/heightmap_fog.frag");
        }
    }

    Shader &setUp() const override {
        Shader *s = foggy ? foggyShader.get() : shader.get();
        s->use();

        // Use cube map
        glActiveTexture(GL_TEXTURE0);
        tex->bind();
        s->setUniform("cubemap", 0);
        s->setUniform("minHeight", minHeight);
        s->setUniform("maxHeight", maxHeight);

        return *s;
    }

    void tearDown() const override {
        tex->unbind();
    }

    std::shared_ptr<Texture2D> tex;

    float minHeight, maxHeight;

    bool foggy = false;


private:

    static inline std::unique_ptr<Shader> shader, foggyShader;
};


#endif //COLORMAPMATERIAL_H
