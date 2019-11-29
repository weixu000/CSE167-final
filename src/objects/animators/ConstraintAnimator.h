#ifndef CONSTRAINTANIMATOR_H
#define CONSTRAINTANIMATOR_H

#include "../Node.h"
#include "../../components/geometries/BezierCurve.h"

class ConstraintAnimator : public Node {
public:
    explicit ConstraintAnimator(std::shared_ptr<BezierCurve> t);

    void update() override;

    bool pause = false;

    bool uniformSpeed = false;

private:
    std::shared_ptr<BezierCurve> track;

    void set();

    float t = 0.0f;
    float velocity = 7.0f;
};


#endif //CONSTRAINTANIMATOR_H
