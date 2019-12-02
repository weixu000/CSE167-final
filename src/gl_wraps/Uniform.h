#ifndef UNIFORM_H
#define UNIFORM_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else

#include <GL/glew.h>

#endif

#include <string>
#include <memory>
#include <list>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class UniformBase {
public:
    std::string name;

    UniformBase(const std::string &name) : name(name) {}

    virtual void set(GLint location) const = 0;
};

template<typename T>
class Uniform : public UniformBase {
public:
    Uniform(const std::string &name, const T &val) : UniformBase(name), val(val) {}

    T val;

    void set(GLint location) const override;
};

using Uniform1i = Uniform<int>;
using Uniform1f = Uniform<float>;
using UniformVec3 = Uniform<glm::vec3>;
using UniformMat4 = Uniform<glm::mat4>;


template<>
inline void Uniform<int>::set(GLint location) const {
    glUniform1i(location, val);
}

template<>
inline void Uniform<float>::set(GLint location) const {
    glUniform1f(location, val);
}

template<>
inline void Uniform<glm::vec3>::set(GLint location) const {
    glUniform3fv(location, 1, glm::value_ptr(val));
}

template<>
inline void Uniform<glm::mat4>::set(GLint location) const {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(val));
}

using UniformPtr = std::unique_ptr<UniformBase>;
using UniformPtrList = std::list<UniformPtr>;

#endif //UNIFORM_H
