#ifndef SKYBOX_H
#define SKYBOX_H

#include "Mesh.h"

class TextureCubemap;

class Skybox : public Mesh {
public:
    Skybox();

    bool cull(const glm::mat4 &view_proj) override { return false; } // default method will cull the cube

    static inline std::shared_ptr<TextureCubemap> cubemap;

protected:
    NodePtr clone() override { return std::make_unique<Skybox>(*this); }
};


#endif //SKYBOX_H
