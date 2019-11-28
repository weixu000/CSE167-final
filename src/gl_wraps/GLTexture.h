#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "GLObject.h"

inline GLuint createTex() {
    GLuint id;
    glGenTextures(1, &id);
    return id;
}

inline void delTex(GLuint id) { glDeleteTextures(1, &id); }

class GLTexture : public GLObject<createTex, delTex> {
public:
    GLTexture() = default;

    void bind(GLenum target) { glBindTexture(target, id); }

    static void unbind(GLenum target) { glBindTexture(target, 0); }

    static void setFilter(GLenum target, GLint min, GLint max) {
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, min);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, max);
    }

    static void setWrap(GLenum target, GLint s, GLint t) {
        glTexParameteri(target, GL_TEXTURE_WRAP_S, s);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, t);
    }
};

#endif //GLTEXTURE_H
