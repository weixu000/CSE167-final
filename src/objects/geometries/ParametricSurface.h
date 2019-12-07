#ifndef PARAMETRICSURFACE_H
#define PARAMETRICSURFACE_H

#include <glm/glm.hpp>


class ParametricSurface {
public:
    virtual glm::vec3 position(float u, float v) = 0;

    virtual glm::vec3 derivativeU(float u, float v) = 0;

    virtual glm::vec3 derivativeV(float u, float v) = 0;

    virtual glm::vec3 normal(float u, float v) {
        return glm::normalize(glm::cross(derivativeV(u, v), derivativeU(u, v)));
    }

    virtual int size() const = 0;
};


#endif //PARAMETRICSURFACE_H
