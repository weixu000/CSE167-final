#ifndef FREEFLYING_H
#define FREEFLYING_H

#include "../Group.h"

class FreeFlying : public Group {
public:
    using Group::Group;

    void update() override;

    // normalized direction in camera space
    void startRotate(const glm::vec3 &dir);

    // normalized direction in camera space
    void rotate(const glm::vec3 &dir);

    void stopRotate();

    static glm::vec3 windowCoordToCamDir(float x, float y,
                                         int width, int height,
                                         const glm::mat4 &proj);

    bool forward = false, left = false, backward = false, right = false, up = false, down = false;
    bool local = true;
    bool freeze = false;

protected:
    NodePtr clone() override { return std::make_unique<FreeFlying>(*this); }

private:
    bool startedRotate = false;
    glm::vec3 initial;
};


#endif //FREEFLYING_H
