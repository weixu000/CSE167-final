#ifndef FLATMATERIAL_H
#define FLATMATERIAL_H

#include "Material.h"
#include "../gl_wraps/Shader.h"

class FlatMaterial : public Material {
public:
    FlatMaterial(const glm::vec3 &color) : color(color) {}

    Shader &setUp() const override {
        auto shader = Shader::flatShader();
        shader->use();
        shader->setUniform("color", color);
        return *shader;
    }

    void tearDown() const override {}

    glm::vec3 color;
};

#endif //FLATMATERIAL_H
