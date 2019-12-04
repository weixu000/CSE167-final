#ifndef WIREFRAMEMATERIAL_H
#define WIREFRAMEMATERIAL_H

#include "FlatMaterial.h"

class WireframeMaterial : public FlatMaterial {
public:
    using FlatMaterial::FlatMaterial;

    Shader &setUp() const override {
        auto &shader = FlatMaterial::setUp();
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        return shader;
    }

    void tearDown() const override {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_CULL_FACE);
    }
};

#include "FlatMaterial.h"

#endif //WIREFRAMEMATERIAL_H
