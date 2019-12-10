#include "Shader.h"

enum ShaderType {
    vertex = GL_VERTEX_SHADER,
    fragment = GL_FRAGMENT_SHADER,
    geometry = GL_GEOMETRY_SHADER
};

GLuint LoadSingleShader(const std::string &shaderFilePath, ShaderType type) {
    // Create a shader id.
    GLuint id = 0;
    id = glCreateShader(type);

    // Try to read shader codes from the shader file.
    std::string code;
    std::ifstream stream(shaderFilePath, std::ios::in);
    if (stream.is_open()) {
        std::string Line;
        while (getline(stream, Line))
            code += "\n" + Line;
        stream.close();
    } else {
        throw std::runtime_error("Cannot open " + shaderFilePath);
    }

    // Compile Shader.
    std::cout << "Compiling shader: " << shaderFilePath << std::endl;
    char const *source = code.c_str();
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    // Check Shader.
    GLint result = GL_FALSE;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    int log_length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        std::string msg(log_length, '\0');
        glGetShaderInfoLog(id, log_length, nullptr, msg.data());
        std::cerr << msg << std::endl;
    }

    if (result != GL_TRUE) {
        throw std::runtime_error("Shader compilation error: " + shaderFilePath);
    }

    return id;
}

void Shader::compileProgram(const std::string &vertexFilePath, const std::string &fragmentFilePath,
                            const std::string &geometryFilePath) {
    // Create the vertex shader and fragment shader.
    auto vertex_id = LoadSingleShader(vertexFilePath, vertex);
    auto fragment_id = LoadSingleShader(fragmentFilePath, fragment);
    auto geometry_id = geometryFilePath.empty() ? 0 : LoadSingleShader(geometryFilePath, geometry);

    // Link the program.
    std::cout << "Linking program" << std::endl;
    glAttachShader(id, vertex_id);
    glAttachShader(id, fragment_id);
    if (geometry_id) glAttachShader(id, geometry_id);
    glLinkProgram(id);

    // Check the program.
    GLint result = GL_FALSE;
    glGetProgramiv(id, GL_LINK_STATUS, &result);
    int log_length;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        std::string msg(log_length, '\0');
        glGetProgramInfoLog(id, log_length, nullptr, msg.data());
        glDeleteProgram(id);
        std::cerr << msg << std::endl;
    }

    if (result != GL_TRUE) {
        throw std::runtime_error(
                "Program link error: " + vertexFilePath + ", " + fragmentFilePath + ", " + geometryFilePath);
    }

    // Detach and delete the shaders as they are no longer needed.
    glDetachShader(id, vertex_id);
    glDetachShader(id, fragment_id);
    if (geometry_id) glDetachShader(id, geometry_id);
    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
    if (geometry_id) glDeleteShader(geometry_id);
}

Shader::Shader(const std::string &vertex_file_path, const std::string &fragment_file_path,
               const std::string &geometry_file_path) {
    compileProgram(vertex_file_path, fragment_file_path, geometry_file_path);

    GLint count;
    glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &count);
    GLint max_len;
    glGetProgramiv(id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_len);
    for (GLint i = 0; i < count; i++) {
        std::string name(max_len, '\0');
        GLsizei length;
        GLint size;
        GLenum type;
        glGetActiveUniform(id, i, max_len, &length, &size, &type, name.data());
        name.resize(length);
        uniformLocations[name] = glGetUniformLocation(id, name.c_str());
    }
}
