#ifndef FLATMATERIAL_H
#define FLATMATERIAL_H

#include "Material.h"
#include "../gl_wraps/Shader.h"

class FlatMaterial : public Material {
public:
    FlatMaterial(const glm::vec3 &color) : color(color) {
        if (!shader) {
            shader = std::make_unique<Shader>("shaders/normal.vert", "shaders/flat.frag");
            foggyShader = std::make_unique<Shader>("shaders/phong.vert", "shaders/flat_fog.frag");
        }
    }

    Shader &setUp() const override {
        Shader *s = foggy ? foggyShader.get() : shader.get();
        s->use();
        s->setUniform("color", color);
        return *s;
    }

    void tearDown() const override {}

    glm::vec3 color;

    bool foggy = false;

private:

    static inline std::unique_ptr<Shader> shader, foggyShader;
};

#endif //FLATMATERIAL_H
