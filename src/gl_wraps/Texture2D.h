#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <string>
#include "../../deps/stb_image/stb_image.h"

#include "GLTexture.h"


class Texture2D : public GLTexture {
public:
    Texture2D() : GLTexture(GL_TEXTURE_2D) {}

    void upload(const std::string &image_path) {
        int width, height, nrChannels;
        auto data = stbi_load(image_path.c_str(), &width, &height, &nrChannels, 0);
        glTexImage2D(
                GL_TEXTURE_2D,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
        );
        stbi_image_free(data);
    }
};

#endif //TEXTURE2D_H
