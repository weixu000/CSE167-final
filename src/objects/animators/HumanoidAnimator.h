#ifndef HUMANOIDANIMATION_H
#define HUMANOIDANIMATION_H

#include <memory>

#include "../Node.h"


class HumanoidAnimator : public Node {
public:
    HumanoidAnimator();

    void update() override;

    std::shared_ptr<Transform> headControl, leftArmControl, rightArmControl, leftLegControl, rightLegControl;
};


#endif //HUMANOIDANIMATION_H
