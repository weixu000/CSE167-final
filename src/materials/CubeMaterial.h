#ifndef CUBEMATERIAL_H
#define CUBEMATERIAL_H

#include "Material.h"
#include "../gl_wraps/Shader.h"
#include "../gl_wraps/TextureCubemap.h"

class CubeMaterial: public Material {
public:
    explicit CubeMaterial(std::shared_ptr<TextureCubemap> cubemap)
    : cubemap(std::move(cubemap)) {
        if (!shader) {
            shader = std::make_unique<Shader>("shaders/cube.vert", "shaders/cube.frag");
        }
    }

    Shader &setUp() const override {
        Shader *s = shader.get();
        s->use();

        // Use cube map
        glActiveTexture(GL_TEXTURE0);
        cubemap->bind();
        s->setUniform("cubemap", 0);

        return *s;
    }

    void tearDown() const override {
        cubemap->unbind();
}

    std::shared_ptr<TextureCubemap> cubemap;

private:
    static inline std::unique_ptr<Shader> shader;
};


#endif //CUBEMATERIAL_H
