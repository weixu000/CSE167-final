#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H

#include "Material.h"
#include "../gl_wraps/Shader.h"

class PhongMaterial : public Material {
public:
    PhongMaterial() {
        if (!shader) {
            shader = std::make_unique<Shader>("shaders/phong.vert", "shaders/phong.frag");
        }
    }

    Shader &setUp() const override {
        shader->use();
        shader->setUniform("ks", ks);
        shader->setUniform("kd", kd);
        shader->setUniform("ka", ka);
        shader->setUniform("alpha", alpha);
        return *shader;
    }


    void tearDown() const override {}

    glm::vec3 ks, kd, ka;
    float alpha;

private:
    static inline std::unique_ptr<Shader> shader;
};


#endif //PHONGMATERIAL_H
