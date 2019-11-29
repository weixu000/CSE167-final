#ifndef HUMANOIDANIMATION_H
#define HUMANOIDANIMATION_H

#include <memory>

#include "../Node.h"


class HumanoidAnimator : public Node {
public:
    HumanoidAnimator();

    void update() override;

    std::shared_ptr<Transform> headControl, leftArmControl, rightArmControl, leftLegControl, rightLegControl;

protected:
    NodePtr clone() override { return std::make_unique<HumanoidAnimator>(*this); }
};


#endif //HUMANOIDANIMATION_H
