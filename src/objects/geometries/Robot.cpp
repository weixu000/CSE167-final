#include <glm/gtx/euler_angles.hpp>

#include "Robot.h"
#include "Wireframe.h"

Robot::Robot(std::shared_ptr<Shader> _shader)
        : shader(std::move(_shader)) {
    auto body = std::make_unique<Mesh>(Mesh::fromObjFile("meshes/Robot-parts-2018/body_s.obj"));
    body->useShader(shader);
    addChild(std::move(body));
    addChild(std::make_unique<Wireframe>(Wireframe::fromAABB(boundingBox())));

    initHead();
    initArms();
    initLegs();
}

Transform *Robot::initHead() {
    auto antenna = Mesh::fromObjFile("meshes/Robot-parts-2018/antenna_s.obj");
    antenna.transform.model = glm::translate(glm::vec3(0.0f, 1.0f, 0.0f)) * glm::scale(glm::vec3(0.3f));
    antenna.useShader(shader);

    auto antenna_l = Node(glm::rotate(glm::pi<float>() / 4, glm::vec3(0.0f, 0.0f, 1.0f)));
    antenna_l.addChild(std::make_unique<Mesh>(antenna));
    auto antenna_r = Node(glm::rotate(-glm::pi<float>() / 4, glm::vec3(0.0f, 0.0f, 1.0f)));
    antenna_r.addChild(std::make_unique<Mesh>(antenna));

    auto eyeball = Mesh::fromObjFile("meshes/Robot-parts-2018/eyeball_s.obj");
    eyeball.transform.model = glm::eulerAngleX(glm::pi<float>() * 0.4f) * glm::translate(glm::vec3(0.0f, 1.0f, 0.0f));
    eyeball.useShader(shader);
    auto eyeball_l = Node(glm::eulerAngleY(glm::pi<float>() * 0.15f));
    eyeball_l.addChild(std::make_unique<Mesh>(eyeball));
    auto eyeball_r = Node(glm::eulerAngleY(glm::pi<float>() * -0.15f));
    eyeball_r.addChild(std::make_unique<Mesh>(eyeball));

    auto head = Mesh::fromObjFile("meshes/Robot-parts-2018/head_s.obj");
    head.useShader(shader);

    auto control = Node();
    control.addChild(std::move(head));
    control.addChild(std::move(antenna_l));
    control.addChild(std::move(antenna_r));
    control.addChild(std::move(eyeball_l));
    control.addChild(std::move(eyeball_r));

    auto head_m = Node(glm::translate(glm::vec3(0.0f, 1.2f, 0.0f)));
    auto control_t = head_m.addChild(std::move(control));
    addChild(std::move(head_m));

    return &control_t->transform;
}

std::tuple<Transform *, Transform *> Robot::initArms() {
    auto arm = Mesh::fromObjFile("meshes/Robot-parts-2018/limb_s.obj");
    arm.transform.model = glm::translate(glm::vec3(0.0f, -0.8f, 0.0f)) * glm::scale(glm::vec3(1.0f, 2.0f, 1.0f));
    arm.useShader(shader);

    auto arm_l = Node();
    arm_l.addChild(arm);
    auto arm_l_b = Node(glm::translate(glm::vec3(-1.4f, 0.6f, 0.0f)));
    auto left_t = arm_l_b.addChild(std::move(arm_l));

    auto arm_r = Node();
    arm_r.addChild(std::move(arm));
    auto arm_r_b = Node(glm::translate(glm::vec3(1.4f, 0.6f, 0.0f)));
    auto right_t = arm_r_b.addChild(std::move(arm_r));

    addChild(std::move(arm_l_b));
    addChild(std::move(arm_r_b));

    return std::make_tuple(&left_t->transform, &right_t->transform);
}

std::tuple<Transform *, Transform *> Robot::initLegs() {
    auto limb = Mesh::fromObjFile("meshes/Robot-parts-2018/limb_s.obj");
    limb.useShader(shader);

    auto leg = Node(glm::translate(glm::vec3(0.0f, -0.7f, 0.0f)));
    leg.addChild(std::make_unique<Mesh>(limb));

    auto leg_l = Node();
    leg_l.addChild(leg);
    auto leg_l_m = std::make_unique<Node>(glm::translate(glm::vec3(-0.5f, -1.0f, 0.0f)));
    auto left_t = leg_l_m->addChild(std::move(leg_l));

    auto leg_r = Node();
    leg_r.addChild(std::move(leg));
    auto leg_r_m = Node(glm::translate(glm::vec3(0.5f, -1.0f, 0.0f)));
    auto right_t = leg_r_m.addChild(std::move(leg_r));

    addChild(std::move(leg_l_m));
    addChild(std::move(leg_r_m));

    return std::make_tuple(&left_t->transform, &right_t->transform);
}
