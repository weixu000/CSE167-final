#ifndef FREEFLYING_H
#define FREEFLYING_H

#include "FreeMover.h"
#include "FreeRotator.h"

class FreeFlying : public FreeMover, public FreeRotator {
public:
    explicit FreeFlying(Camera *cam, const glm::mat4 &t = glm::mat4(1.0f))
            : Group(t), FreeRotator(cam) {}

protected:
    NodePtr clone() override { return std::make_unique<FreeFlying>(*this); }
};


#endif //FREEFLYING_H
