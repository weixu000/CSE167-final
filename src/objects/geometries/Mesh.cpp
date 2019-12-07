#include <iostream>
#include <fstream>
#include <map>
#include <tuple>
#include <numeric>
#include <glm/gtx/transform.hpp>

#include "Mesh.h"
#include "../Camera.h"
#include "../../materials/Material.h"
#include "../../gl_wraps/Shader.h"
#include "../../gl_wraps/GLBuffer.h"
#include "../../gl_wraps/GLVertexArray.h"

Mesh::Mesh(const std::vector<glm::vec3> &attrs, const std::vector<GLuint> &indices) {
    count = indices.size();

    const auto inf = std::numeric_limits<float>::infinity();
    glm::vec3 minVal(inf, inf, inf), maxVal(-inf, -inf, -inf);
    for (auto it = attrs.begin(); it != attrs.end(); it += 2) {
        minVal = glm::min(minVal, *it);
        maxVal = glm::max(maxVal, *it);
    }
    bb = {minVal, maxVal};

    vao = std::make_shared<GLVertexArray>();

    // Bind to the VAO.
    vao->bind();

    GLBuffer vbo, ebo;

    // Pass in the data.
    vbo.upload(sizeof(glm::vec3) * attrs.size(), attrs.data());
    // Enable vertex attribute 0.
    // We will be able to access points through it.
    vao->setAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          2 * sizeof(glm::vec3));
    // Enable vertex attribute 1.
    // We will be able to access normals through it.
    vao->setAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          2 * sizeof(glm::vec3), sizeof(glm::vec3));
    GLBuffer::unbind();

    ebo.bind(GL_ELEMENT_ARRAY_BUFFER);
    // Pass in the data.
    ebo.upload(sizeof(GLuint) * indices.size(), indices.data(), GL_ELEMENT_ARRAY_BUFFER);

    // Unbind from the VAO.
    vao->unbind();
}

void Mesh::draw(const glm::mat4 &world, const Camera &camera) {
    assert(material);
    auto &shader = material->setUp();
    camera.setUniform(shader);
    shader.setUniform("model", world * transform.model);

    // Bind to the VAO.
    vao->bind();
    // Draw points
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    // Unbind from the VAO.
    vao->unbind();

    material->tearDown();
}

Mesh Mesh::fromObjFile(const std::string &objFilename) {
    std::ifstream objFile(objFilename);
    if (!objFile.is_open()) {
        std::cerr << "Can't open the file " << objFilename << std::endl;
        return Mesh();
    }
    std::vector<glm::vec3> vertices, normals;
    std::vector<GLuint> faces;
    while (objFile) {
        std::string label;
        objFile >> label;
        if (label == "v") {
            glm::vec3 p;
            objFile >> p.x >> p.y >> p.z;
            vertices.push_back(p);
        } else if (label == "vn") {
            glm::vec3 n;
            objFile >> n.x >> n.y >> n.z;
            normals.push_back(glm::normalize(n));
        } else if (label == "f") {
            for (int i = 0; i < 3; ++i) {
                GLuint v, n;
                objFile >> v;
                faces.push_back(v - 1);
                objFile.ignore(std::numeric_limits<std::streamsize>::max(), '/');
                objFile.ignore(std::numeric_limits<std::streamsize>::max(), '/');
                objFile >> n;
                faces.push_back(n - 1);
            }
        }
        objFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    objFile.close();

    std::vector<glm::vec3> attrs; // vertices and normals interleaved
    std::vector<GLuint> indices;

    // Use std::map to record each different vertex/normal pairs
    std::map<std::tuple<GLuint, GLuint>, GLuint> indices_map;
    for (auto it_f = faces.begin(); it_f != faces.end(); it_f += 2) {
        GLuint v = *it_f, n = *(it_f + 1);
        auto[it_m, inserted] = indices_map.insert(std::make_pair(std::make_tuple(v, n), attrs.size() >> 1));
        if (inserted) {
            attrs.push_back(vertices[v]);
            attrs.push_back(normals[n]);
        }
        indices.push_back(it_m->second);
    }
    std::cout << objFilename << " " << (attrs.size() >> 1) << std::endl;

    return Mesh(attrs, indices);
}

Mesh Mesh::faceNormalMesh(const std::vector<glm::vec3> &vertices, const std::vector<GLuint> &indices) {
    std::vector<glm::vec3> attrs;
    for (size_t i = 0; i < indices.size(); i += 3) {
        std::array<glm::vec3, 3> p = {vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]]};
        auto normal = glm::cross(p[1] - p[0], p[2] - p[0]);
        for (auto &v:p) {
            attrs.push_back(v);
            attrs.push_back(normal);
        }
    }

    std::vector<GLuint> new_indices(attrs.size() / 2);
    std::iota(new_indices.begin(), new_indices.end(), 0);

    return Mesh(attrs, new_indices);
}

Mesh Mesh::fromAABB(const AABB &bb) {
    std::vector<glm::vec3> vertices(bb.vertices.begin(), bb.vertices.end());
    std::vector<GLuint> indices{
            0, 2, 1, 0, 3, 2,
            0, 1, 4, 1, 5, 4,
            0, 7, 3, 0, 4, 7,
            0, 2, 1, 0, 3, 2,
            1, 2, 5, 2, 6, 5,
            2, 3, 6, 3, 7, 6,
            4, 5, 6, 4, 6, 7
    };
    return faceNormalMesh(vertices, indices);
}

Mesh Mesh::cube() {
    return fromAABB(AABB(glm::vec3(-1.0f), glm::vec3(1.0f)));
}
