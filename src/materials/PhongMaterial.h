#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H

#include "Material.h"
#include "../gl_wraps/Shader.h"

class PhongMaterial : public Material {
public:
    PhongMaterial() {
        if (!shader) {
            shader = std::make_unique<Shader>("shaders/phong.vert", "shaders/phong.frag");
            foggyShader = std::make_unique<Shader>("shaders/phong.vert", "shaders/phong_fog.frag");
        }
    }

    Shader &setUp() const override {
        Shader *s = foggy ? foggyShader.get() : shader.get();
        s->use();
        s->setUniform("ks", ks);
        s->setUniform("kd", kd);
        s->setUniform("ka", ka);
        s->setUniform("alpha", alpha);
        return *s;
    }


    void tearDown() const override {}

    glm::vec3 ks, kd, ka;
    float alpha;

    bool foggy = false;

private:
    static inline std::unique_ptr<Shader> shader, foggyShader;
};


#endif //PHONGMATERIAL_H
