#ifndef FINALPROJECT_NORMALMATERIAL_H
#define FINALPROJECT_NORMALMATERIAL_H

#include "Material.h"
#include "../gl_wraps/Shader.h"

class NormalMaterial : public Material {
public:
    Shader &setUp() const override {
        auto shader = Shader::normalShader();
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
};

#include "Material.h"
#include "../gl_wraps/Shader.h"

#endif //FINALPROJECT_NORMALMATERIAL_H
