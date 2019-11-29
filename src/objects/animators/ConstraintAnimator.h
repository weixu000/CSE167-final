#ifndef CONSTRAINTANIMATOR_H
#define CONSTRAINTANIMATOR_H

#include "../Node.h"
#include "../geometries/BezierCurve.h"

class ConstraintAnimator : public Node {
public:
    explicit ConstraintAnimator(BezierCurve *t);

    void update() override;

    bool pause = false;

    bool uniformSpeed = false;

protected:
    NodePtr clone() override { return std::make_unique<ConstraintAnimator>(*this); }

private:
    BezierCurve *track;

    void set();

    float t = 0.0f;
    float velocity = 7.0f;
};


#endif //CONSTRAINTANIMATOR_H
