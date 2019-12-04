#ifndef REFLECTIONMAPMATERIAL_H
#define REFLECTIONMAPMATERIAL_H

#include "Material.h"
#include "../gl_wraps/TextureCubemap.h"
#include "../gl_wraps/Shader.h"


class ReflectionMapMaterial : public Material {
public:
    explicit ReflectionMapMaterial(std::shared_ptr<TextureCubemap> cubemap)
            : cubemap(std::move(cubemap)) {
        if (!shader) {
            shader = std::make_unique<Shader>("shaders/phong.vert", "shaders/reflection_map.frag");
        }
    }

    Shader &setUp() const override {
        shader->use();

        // Use cube map
        glActiveTexture(GL_TEXTURE0);
        cubemap->bind();
        shader->setUniform("cubemap", 0);

        return *shader;
    }

    void tearDown() const override {
        cubemap->unbind();
    }

    std::shared_ptr<TextureCubemap> cubemap;

private:
    static inline std::unique_ptr<Shader> shader;
};


#endif //REFLECTIONMAPMATERIAL_H
