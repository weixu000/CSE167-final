#ifndef ROBOT_H
#define ROBOT_H

#include "Geometry.h"
#include "Mesh.h"


class Robot : public Geometry {
public:
    Robot(std::shared_ptr<Shader> shader);

    AABB boundingBox() const override { return bb; }

protected:
    NodePtr clone() override { return std::make_unique<Robot>(*this); }

    Transform *initHead();

    std::tuple<Transform *, Transform *> initArms();

    std::tuple<Transform *, Transform *> initLegs();

private:
    std::shared_ptr<Shader> shader;

    const AABB bb{glm::vec3(-1.6f, -2.2f, -1.5f), glm::vec3(1.6f, 2.5f, 1.5f)};
};


#endif //ROBOT_H
