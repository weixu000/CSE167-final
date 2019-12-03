#ifndef FREEMOVER_H
#define FREEMOVER_H

#include "../Group.h"

class FreeMover : virtual public Group {
public:
    using Group::Group;

    void update() override;

    void onKeyPress(Key key, int mods) override;

    void OnKeyRelease(int key, int mods) override;

    Key forwardKey = GLFW_KEY_W, backwardKey = GLFW_KEY_S,
            leftKey = GLFW_KEY_A, rightKey = GLFW_KEY_D,
            upKey = GLFW_KEY_Q, downKey = GLFW_KEY_E;

protected:
    NodePtr clone() override { return std::make_unique<FreeMover>(*this); }

    bool forward = false, left = false, backward = false, right = false, up = false, down = false;
};


#endif //FREEMOVER_H
