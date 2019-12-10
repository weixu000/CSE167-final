#ifndef FLATMATERIAL_H
#define FLATMATERIAL_H

#include "Material.h"
#include "../gl_wraps/Shader.h"

class FlatMaterial : public Material {
public:
    FlatMaterial(const glm::vec3 &color) : color(color) {
        if (!shader) {
            shader = std::make_unique<Shader>("shaders/normal.vert", "shaders/flat.frag");
        }
    }

    Shader &setUp() const override {
        shader->use();
        shader->setUniform("color", color);
        return *shader;
    }

    void tearDown() const override {}

    glm::vec3 color;
private:
    static inline std::unique_ptr<Shader> shader;
};

#endif //FLATMATERIAL_H
