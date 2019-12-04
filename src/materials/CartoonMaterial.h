#ifndef CARTOONMATERIAL_H
#define CARTOONMATERIAL_H

#include "Material.h"
#include "../gl_wraps/Shader.h"

class CartoonMaterial : public Material {
public:
    CartoonMaterial() {
        if (!shader) {
            shader = std::make_unique<Shader>("shaders/phong.vert", "shaders/cartoon.frag");
        }
    }

    Shader &setUp() const override {
        shader->use();
        return *shader;
    }

    void tearDown() const override {}

private:
    static inline std::unique_ptr<Shader> shader;
};


#endif //CARTOONMATERIAL_H
