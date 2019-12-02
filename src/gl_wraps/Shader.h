#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <memory>

#include <glm/glm.hpp>
#include "GLObject.h"
#include "Uniform.h"

inline GLuint createProgram() { return glCreateProgram(); };

inline void delProgram(GLuint id) { glDeleteProgram(id); };

class Shader : public GLObject<createProgram, delProgram> {
public:
    Shader() = default;

    Shader(const std::string &vertex_file_path, const std::string &fragment_file_path,
           const std::string &geometry_file_path = "");

    void use() { glUseProgram(id); }

    void setUniform(const UniformBase &uniform) {
        auto iter = uniformLocations.find(uniform.name);
        if (iter != uniformLocations.end()) {
            uniform.set(iter->second);
        }
    }

    template<typename T>
    void setUniform(const std::string &name, const T &val) {
        setUniform(Uniform<T>(name, val));
    }

    static std::shared_ptr<Shader> flatShader();

private:
    std::unordered_map<std::string, GLint> uniformLocations;


    void compileProgram(const std::string &vertexFilePath, const std::string &fragmentFilePath,
                        const std::string &geometryFilePath);
};

#endif
