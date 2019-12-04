#include "Wireframe.h"
#include "../../gl_wraps/Shader.h"
#include "../Camera.h"

Wireframe::Wireframe(const std::vector<glm::vec3> &vertices, const std::vector<GLuint> &indices) {
    upload(vertices, indices);
}

void Wireframe::upload(const std::vector<glm::vec3> &vertices, const std::vector<GLuint> &indices) {
    count = indices.size();

    const auto inf = std::numeric_limits<float>::infinity();
    glm::vec3 minVal(inf, inf, inf), maxVal(-inf, -inf, -inf);
    for (auto &v:vertices) {
        minVal = glm::min(minVal, v);
        maxVal = glm::max(maxVal, v);
    }
    bb = {minVal, maxVal};

    // Bind to the VAO.
    vao->bind();

    // Pass in the data.
    vbo->upload(sizeof(glm::vec3) * vertices.size(), vertices.data());
    // Enable vertex attribute 0.
    vao->setAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          sizeof(glm::vec3));
    vbo->unbind();

    ebo->bind(GL_ELEMENT_ARRAY_BUFFER);
    // Pass in the data.
    ebo->upload(sizeof(GLuint) * indices.size(), indices.data(), GL_ELEMENT_ARRAY_BUFFER);

    // Unbind from the VAO.
    vao->unbind();
}

void Wireframe::draw(const glm::mat4 &world, const Camera &camera) {
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

Wireframe Wireframe::fromAABB(const AABB &bb) {
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
    return Wireframe(vertices, indices);
}
