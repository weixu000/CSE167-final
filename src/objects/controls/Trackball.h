#ifndef TRACKBALL_H
#define TRACKBALL_H

#include <glm/glm.hpp>

#include "../Group.h"

class Trackball : public Group {
public:
    explicit Trackball(Camera *cam, const glm::mat4 &t = glm::mat4(1.0f))
            : Group(t), camera(cam) {}

    void onMouseMove(float x, float y) override;

    void onMouseButtonPress(MouseButton button, int mods, float x, float y) override;

    void onMouseButtonRelease(MouseButton button, int mods, float x, float y) override;

    void scale(float offset);

protected:
    NodePtr clone() override { return std::make_unique<Trackball>(*this); }

private:
    static glm::vec3 viewportToTrackball(float x, float y);

    bool started = false;
    glm::mat4 orientation{1.0f};
    glm::vec3 initial;

    // x,y should be normalized
    void start(float x, float y);

    // x,y should be normalized
    void move(float x, float y);

    void stop();

    Camera *camera;
};


#endif // TRACKBALL_H
