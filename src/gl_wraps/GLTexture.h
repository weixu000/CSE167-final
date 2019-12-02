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
    explicit GLTexture(GLenum target) : target(target) {}

    void bind() { glBindTexture(target, id); }

    void unbind() { glBindTexture(target, 0); }

    void setFilter(GLint min, GLint max) {
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, min);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, max);
    }

    void setWrap(GLint s, GLint t) {
        glTexParameteri(target, GL_TEXTURE_WRAP_S, s);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, t);
    }

    const GLenum target;

};

#endif //GLTEXTURE_H
