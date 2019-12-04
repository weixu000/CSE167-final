#include <random>
#include <ctime>

#include "Terrain.h"
#include "../Camera.h"

std::unique_ptr<Shader> Terrain::shader;

Terrain::HeightMap Terrain::diamondSquare(int n, const std::array<float, 4> &corners, float height_range) {
    const auto nan = std::numeric_limits<float>::quiet_NaN();
    n = (1 << n) + 1;
    HeightMap height(n, std::vector<float>(n, nan));
    height[0][0] = corners[0];
    height[0][n - 1] = corners[1];
    height[n - 1][n - 1] = corners[2];
    height[n - 1][0] = corners[3];

    std::default_random_engine rand_eng(static_cast<long unsigned int>(time(0)));

    for (auto step_size = n - 1; step_size > 1; step_size /= 2) {
        std::uniform_real_distribution<float> dist(-height_range * step_size / n, height_range * step_size / n);

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

Terrain::Terrain(int n, const std::array<float, 4> &corners, float height_range) {
    if (!shader) {
        shader = std::make_unique<Shader>("shaders/terrain.vert", "shaders/terrain.frag");
    }

    heights = diamondSquare(n, corners, height_range);
    auto size = heights.size();

    std::vector<glm::vec3> vertices;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            vertices.emplace_back(i, heights[i][j], j);
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

void Terrain::draw(const glm::mat4 &world, const Camera &camera) {
    auto m = world * transform.model;

    glActiveTexture(GL_TEXTURE0);
    tex->bind();

    shader->use();
    camera.setUniform(*shader);
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


// v
// ^
// 3  2
// 0  1 > u
std::tuple<float, float, glm::vec3, glm::vec3, glm::vec3, glm::vec3> Terrain::patch(float u, float v) {
    auto i = int(std::floor(u));
    u -= i;

    auto j = int(std::floor(v));
    v -= j;

    return std::make_tuple(
            u, v,
            glm::vec3(i, heights[i][j], j), glm::vec3(i + 1, heights[i + 1][j], j),
            glm::vec3(i + 1, heights[i + 1][j + 1], j + 1), glm::vec3(i, heights[i][j + 1], j + 1));
}

glm::vec3 Terrain::position(float u_, float v_) {
    auto[u, v, p0, p1, p2, p3] = patch(u_, v_);

    if (u + v <= 1) {
        return p0 + u * (p1 - p0) + v * (p3 - p0);
    } else {
        return p2 + (1 - u) * (p3 - p2) + (1 - v) * (p1 - p2);
    }
}

glm::vec3 Terrain::derivativeU(float u_, float v_) {
    auto[u, v, p0, p1, p2, p3] = patch(u_, v_);
    if (u + v <= 1) {
        return p1 - p0;
    } else {
        return p2 - p3;
    }
}

glm::vec3 Terrain::derivativeV(float u_, float v_) {
    auto[u, v, p0, p1, p2, p3] = patch(u_, v_);
    if (u + v <= 1) {
        return p3 - p0;
    } else {
        return p2 - p1;
    }
}
