#ifndef FREEROTATOR_H
#define FREEROTATOR_H

#include "../Group.h"

class Camera;

class FreeRotator : virtual public Group {
public:
    explicit FreeRotator(Camera *cam, const glm::mat4 &t = glm::mat4(1.0f))
            : Group(t), camera(cam) {}

    void onMouseMove(float x, float y) override;

    void onMouseButtonPress(MouseButton button, int mods, float x, float y) override;

    void onMouseButtonRelease(MouseButton button, int mods, float x, float y) override;

protected:
    NodePtr clone() override { return std::make_unique<FreeRotator>(*this); }

private:
    bool startedRotate = false;
    glm::vec2 previous;
    float eulerX = 0.0f, eulerY = 0.0f;

    Camera *camera;

    void rotate(const glm::vec2 &current);
};


#endif //FREEROTATOR_H
