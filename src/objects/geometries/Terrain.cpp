#include <random>

#include "Terrain.h"

std::unique_ptr<Shader> Terrain::shader;

Terrain::HeightMap Terrain::diamondSquare(int n, const std::array<float, 4> &corners) {
    const auto nan = std::numeric_limits<float>::quiet_NaN();
    n = (1 << n) + 1;
    HeightMap height(n, std::vector<float>(n, nan));
    height[0][0] = corners[0];
    height[0][n - 1] = corners[1];
    height[n - 1][n - 1] = corners[2];
    height[n - 1][0] = corners[3];

    std::random_device rd;
    std::default_random_engine rand_eng(rd());

    for (auto step_size = n - 1; step_size > 1; step_size /= 2) {
        std::uniform_real_distribution<float> dist(-10.0f * step_size / n, 10.0f * step_size / n);

        // Diamond step
        for (int x1 = 0, x2 = step_size; x2 < n; x1 += step_size, x2 += step_size) {
            for (int y1 = 0, y2 = step_size; y2 < n; y1 += step_size, y2 += step_size) {
                // Four corners: (x1,y1), (x1,y2), (x2,y2), (x2,y1)
                height[(x1 + x2) / 2][(y1 + y2) / 2] =
                        dist(rand_eng) + (height[x1][y1] + height[x1][y2] + height[x2][y2] + height[x2][y1]) / 4;
            }
        }

        // Square step
        for (int x = 0, y_ = step_size / 2; x < n; x += step_size / 2, y_ = step_size / 2 - y_) {
            for (int y = y_; y < n; y += step_size) {
                height[x][y] = 0.0f;
                int num = 0;
                if (x - step_size / 2 >= 0) {
                    height[x][y] += height[x - step_size / 2][y];
                    num += 1;
                }
                if (y + step_size / 2 < n) {
                    height[x][y] += height[x][y + step_size / 2];
                    num += 1;
                }
                if (x + step_size / 2 < n) {
                    height[x][y] += height[x + step_size / 2][y];
                    num += 1;
                }
                if (y - step_size / 2 >= 0) {
                    height[x][y] += height[x][y - step_size / 2];
                    num += 1;
                }
                height[x][y] = height[x][y] / num + dist(rand_eng);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            assert(!std::isnan(height[i][j]));
        }
    }

    return height;
}

Terrain::Terrain(int n, const std::array<float, 4> &corners) {
    if (!shader) {
        shader = std::make_unique<Shader>("shaders/terrain.vert", "shaders/terrain.frag");
    }

    auto height = diamondSquare(n, corners);
    auto size = height.size();

    std::vector<glm::vec3> vertices;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            vertices.emplace_back(i, height[i][j], j);
        }
    }

    std::vector<GLuint> indices;
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            indices.push_back(i * size + j);
            indices.push_back(i * size + j + 1);
            indices.push_back((i + 1) * size + j);

            indices.push_back((i + 1) * size + j);
            indices.push_back(i * size + j + 1);
            indices.push_back((i + 1) * size + j + 1);
        }
    }

    upload(vertices, indices);

    tex = std::make_shared<Texture2D>();
    tex->bind();
    tex->upload("textures/earth.png");
    tex->setFilter(GL_LINEAR, GL_LINEAR);
    tex->setWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    tex->unbind();
}

void Terrain::draw(const glm::mat4 &world, const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &eye) {
    auto m = world * transform.model;

    glActiveTexture(GL_TEXTURE0);
    tex->bind();

    shader->use();
    shader->setUniform("projection", projection);
    shader->setUniform("view", view);
    shader->setUniform("model", world);
    shader->setUniform("colormap", 0);
    shader->setUniform("minHeight", bb.vertices[0].y);
    shader->setUniform("maxHeight", bb.vertices[4].y);
    // Bind to the VAO.
    vao->bind();
    // Draw points
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    // Unbind from the VAO.
    vao->unbind();
}
