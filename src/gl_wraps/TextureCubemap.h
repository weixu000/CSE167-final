#ifndef TEXTURECUBEMAP_H
#define TEXTURECUBEMAP_H

#include <string>
#include "../../deps/stb_image/stb_image.h"

#include "GLTexture.h"

class TextureCubemap : public GLTexture {
public:
    TextureCubemap() : GLTexture(GL_TEXTURE_CUBE_MAP) {}

    void upload(const std::array<std::string, 6> &image_path) {
        for (size_t i = 0; i < 6; ++i) {
            int width, height, nrChannels;
            auto data = stbi_load(image_path[i].c_str(), &width, &height, &nrChannels, 0);
            glTexImage2D(
                    GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
    }
};


#endif //TEXTURECUBEMAP_H
