#ifndef FREEROTATOR_H
#define FREEROTATOR_H

#include "../Group.h"

class Camera;

class FreeRotator : virtual public Group {
public:
    explicit FreeRotator(Camera *cam, const glm::mat4 &t = glm::mat4(1.0f))
            : Group(t), camera(cam) {}

    // normalized direction in camera space
    void startRotate(const glm::vec3 &dir);

    // normalized direction in camera space
    void rotate(const glm::vec3 &dir);

    void stopRotate();

    glm::vec3 windowCoordToCamDir(float x, float y);

    void onMouseMove(float x, float y) override;

    void onMouseButtonPress(MouseButton button, int mods, float x, float y) override;

    void onMouseButtonRelease(MouseButton button, int mods, float x, float y) override;

protected:
    NodePtr clone() override { return std::make_unique<FreeRotator>(*this); }

private:
    bool startedRotate = false;
    glm::vec3 initial;

    Camera *camera;
};


#endif //FREEROTATOR_H
