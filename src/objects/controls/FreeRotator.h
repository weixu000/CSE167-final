#ifndef FREEROTATOR_H
#define FREEROTATOR_H

#include "../Group.h"


class FreeRotator : virtual public Group {
public:
    using Group::Group;

    // normalized direction in camera space
    void startRotate(const glm::vec3 &dir);

    // normalized direction in camera space
    void rotate(const glm::vec3 &dir);

    void stopRotate();

    static glm::vec3 windowCoordToCamDir(float x, float y,
                                         int width, int height,
                                         const glm::mat4 &proj);

protected:
    NodePtr clone() override { return std::make_unique<FreeRotator>(*this); }

private:
    bool startedRotate = false;
    glm::vec3 initial;
};


#endif //FREEROTATOR_H
