#include "stb_image.h"

#include "Skybox.h"
#include "../Camera.h"
#include "../../gl_wraps/TextureCubemap.h"

Skybox::Skybox()
        : Mesh(Mesh::cube()) { // Skybox is just a cube
    if (!cubemap) {
        cubemap = std::make_shared<TextureCubemap>();
        cubemap->bind();
        cubemap->upload({
                                "textures/prof_schulze_square.jpg",
                                "textures/prof_schulze_square.jpg",
                                "textures/prof_schulze_square.jpg",
                                "textures/prof_schulze_square.jpg",
                                "textures/prof_schulze_square.jpg",
                                "textures/prof_schulze_square.jpg"
                        });
        // Use bilinear interpolation:
        cubemap->setFilter(GL_LINEAR, GL_LINEAR);

        // Use clamp to edge to hide skybox edges:
        cubemap->setWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
        cubemap->unbind();
    }
}