#ifndef FINALPROJECT_NORMALMATERIAL_H
#define FINALPROJECT_NORMALMATERIAL_H

#include "Material.h"
#include "../gl_wraps/Shader.h"

class NormalMaterial : public Material {
public:
    NormalMaterial() {
        if (!shader) {
            shader = std::make_unique<Shader>("shaders/normal.vert", "shaders/normal.frag");
        }
    }


    Shader &setUp() const override {
        shader->use();
        return *shader;
    }

    void tearDown() const override {}

    static std::shared_ptr<NormalMaterial> singleton() {
        static std::shared_ptr<NormalMaterial> material;
        if (!material) {
            material = std::make_shared<NormalMaterial>();
        }
        return material;
    }

private:
    static inline std::unique_ptr<Shader> shader;
};

#endif //FINALPROJECT_NORMALMATERIAL_H
