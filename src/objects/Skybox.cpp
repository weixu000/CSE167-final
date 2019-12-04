#include "../../deps/stb_image/stb_image.h"

#include "Skybox.h"
#include "Camera.h"
#include "../materials/SkyboxMaterial.h"

Skybox::Skybox() {
    if (!cube) {
        cubemap = std::make_shared<TextureCubemap>();
        cubemap->bind();
        cubemap->upload({
                                "textures/Skybox_Water222_right.jpg",
                                "textures/Skybox_Water222_left.jpg",
                                "textures/Skybox_Water222_top.jpg",
                                "textures/Skybox_Water222_base.jpg",
                                "textures/Skybox_Water222_front.jpg",
                                "textures/Skybox_Water222_back.jpg"
                        });
        // Use bilinear interpolation:
        cubemap->setFilter(GL_LINEAR, GL_LINEAR);

        // Use clamp to edge to hide skybox edges:
        cubemap->setWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
        cubemap->unbind();

        auto material = std::make_shared<SkyboxMaterial>(cubemap);
        cube = std::make_shared<Mesh>(Mesh::cube());
        cube->material = material;
    }
}