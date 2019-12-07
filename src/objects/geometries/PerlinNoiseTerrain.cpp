#include <random>
#include <chrono>
#include <iostream>

#include "PerlinNoiseTerrain.h"

PerlinNoiseTerrain::PerlinNoiseTerrain(int n, int tessellation)
        : gradients(n, std::vector<glm::vec2>(n)) {
    auto now = std::chrono::system_clock::now();
    std::default_random_engine eng(now.time_since_epoch().count());
    std::uniform_real_distribution<float> dist(-1, 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            gradients[i][j] = glm::normalize(glm::vec2(dist(eng), dist(eng)));
        }
    }

    std::vector<glm::vec3> attrs;
    for (int i = 0; i < tessellation; ++i) {
        for (int j = 0; j < tessellation; ++j) {
            auto u = float(i) / (tessellation - 1) * (n - 1), v = float(j) / (tessellation - 1) * (n - 1);
            attrs.emplace_back(position(u, v));
            attrs.emplace_back(normal(u, v));
        }
    }

    std::vector<GLuint> indices;
    for (int i = 0; i < tessellation - 1; ++i) {
        for (int j = 0; j < tessellation - 1; ++j) {
            indices.push_back(i * tessellation + j);
            indices.push_back(i * tessellation + j + 1);
            indices.push_back((i + 1) * tessellation + j);

            indices.push_back((i + 1) * tessellation + j);
            indices.push_back(i * tessellation + j + 1);
            indices.push_back((i + 1) * tessellation + j + 1);
        }
    }

    Mesh::operator=(Mesh(attrs, indices));
}

// y
// ^
// 2  3
// 0  1 > x
std::tuple<float, float, glm::vec2, glm::vec2, glm::vec2, glm::vec2> PerlinNoiseTerrain::grid(float x, float y) {
    auto i = int(std::floor(x));
    auto j = int(std::floor(y));
    if (x == i && i) {
        i -= 1;
    }
    if (y == j && j) {
        j -= 1;
    }

    x -= i;
    y -= j;

    return std::make_tuple(x, y,
                           glm::vec2(gradients[i][j]), glm::vec2(gradients[i + 1][j]),
                           glm::vec2(gradients[i][j + 1]), glm::vec2(gradients[i + 1][j + 1]));
}

float PerlinNoiseTerrain::perlin(float x_, float y_) {
    auto[x, y, g0, g1, g2, g3] = grid(x_, y_);

    auto s = glm::dot(g0, glm::vec2(x, y));
    auto t = glm::dot(g1, glm::vec2(x, y) - glm::vec2(1, 0));
    auto u = glm::dot(g2, glm::vec2(x, y) - glm::vec2(0, 1));
    auto v = glm::dot(g3, glm::vec2(x, y) - glm::vec2(1, 1));

    auto xs = glm::smoothstep(0.0f, 1.0f, x);
    auto ys = glm::smoothstep(0.0f, 1.0f, y);

    auto z1 = glm::mix(s, t, xs), z2 = glm::mix(u, v, xs);

    return glm::mix(z1, z2, ys);
}

float PerlinNoiseTerrain::perlinX(float x_, float y_) {
    auto[x, y, g0, g1, g2, g3] = grid(x_, y_);

    auto s = glm::dot(g0, glm::vec2(x, y));
    auto t = glm::dot(g1, glm::vec2(x, y) - glm::vec2(1, 0));
    auto u = glm::dot(g2, glm::vec2(x, y) - glm::vec2(0, 1));
    auto v = glm::dot(g3, glm::vec2(x, y) - glm::vec2(1, 1));
    auto s_x = g0.x, t_x = g1.x, u_x = g2.x, v_x = g3.x;

    auto xs = glm::smoothstep(0.0f, 1.0f, x);
    auto ys = glm::smoothstep(0.0f, 1.0f, y);
    auto xs_x = 6 * x * (1 - x), ys_x = 0.0f;

    auto z1 = glm::mix(s, t, xs), z2 = glm::mix(u, v, xs);
    auto z1_x = s_x * (1 - xs) - s * xs_x + t_x * xs + t * xs_x;
    auto z2_x = u_x * (1 - xs) - u * xs_x + v_x * xs + v * xs_x;

    auto z = glm::mix(z1, z2, ys);
    auto zx = z1_x * (1 - ys) - z1 * ys_x + z2_x * ys + z2 * ys_x;
    return zx;
}

float PerlinNoiseTerrain::perlinY(float x_, float y_) {
    auto[x, y, g0, g1, g2, g3] = grid(x_, y_);

    auto s = glm::dot(g0, glm::vec2(x, y));
    auto t = glm::dot(g1, glm::vec2(x, y) - glm::vec2(1, 0));
    auto u = glm::dot(g2, glm::vec2(x, y) - glm::vec2(0, 1));
    auto v = glm::dot(g3, glm::vec2(x, y) - glm::vec2(1, 1));
    auto s_y = g0.y, t_y = g1.y, u_y = g2.y, v_y = g3.y;

    auto xs = glm::smoothstep(0.0f, 1.0f, x);
    auto ys = glm::smoothstep(0.0f, 1.0f, y);
    auto xs_y = 0.0f, ys_y = 6 * y * (1 - y);

    auto z1 = glm::mix(s, t, xs), z2 = glm::mix(u, v, xs);
    auto z1_y = s_y * (1 - xs) - s * xs_y + t_y * xs + t * xs_y;
    auto z2_y = u_y * (1 - xs) - u * xs_y + v_y * xs + v * xs_y;

    auto z = glm::mix(z1, z2, ys);
    auto z_y = z1_y * (1 - ys) - z1 * ys_y + z2_y * ys + z2 * ys_y;
    return z_y;
}
