#ifndef ROBOT_H
#define ROBOT_H

#include "Geometry.h"
#include "Mesh.h"


class Robot : public Geometry {
public:
    Robot(std::shared_ptr<Shader> shader);

    void
    draw(const glm::mat4 &world, const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &eye) override;

    AABB boundingBox() const override { return bb; }

protected:
    NodePtr clone() override { return std::make_unique<Robot>(*this); }

private:
    Node root;

    std::shared_ptr<Shader> shader;

    const AABB bb{glm::vec3(-1.6f, -2.2f, -1.5f), glm::vec3(1.6f, 2.5f, 1.5f)};

    void initHead();

    void initArms();

    void initLegs();
};


#endif //ROBOT_H
