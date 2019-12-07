#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

#include "Robot.h"
#include "Mesh.h"

namespace {
    Transform *initHead(Group &root, std::shared_ptr<Material> material) {
        auto antenna = Mesh::fromObjFile("meshes/Robot-parts-2018/antenna_s.obj");
        antenna.transform.model = glm::translate(glm::vec3(0.0f, 1.0f, 0.0f)) * glm::scale(glm::vec3(0.3f));
        antenna.material = material;

        auto antenna_l = Group(glm::rotate(glm::pi<float>() / 4, glm::vec3(0.0f, 0.0f, 1.0f)));
        antenna_l.addChild(std::make_unique<Mesh>(antenna));
        auto antenna_r = Group(glm::rotate(-glm::pi<float>() / 4, glm::vec3(0.0f, 0.0f, 1.0f)));
        antenna_r.addChild(std::make_unique<Mesh>(antenna));

        auto eyeball = Mesh::fromObjFile("meshes/Robot-parts-2018/eyeball_s.obj");
        eyeball.transform.model =
                glm::eulerAngleX(glm::pi<float>() * 0.4f) * glm::translate(glm::vec3(0.0f, 1.0f, 0.0f));
        eyeball.material = material;
        auto eyeball_l = Group(glm::eulerAngleY(glm::pi<float>() * 0.15f));
        eyeball_l.addChild(std::make_unique<Mesh>(eyeball));
        auto eyeball_r = Group(glm::eulerAngleY(glm::pi<float>() * -0.15f));
        eyeball_r.addChild(std::make_unique<Mesh>(eyeball));

        auto head = Mesh::fromObjFile("meshes/Robot-parts-2018/head_s.obj");
        head.material = material;

        auto control = Group();
        control.addChild(std::move(head));
        control.addChild(std::move(antenna_l));
        control.addChild(std::move(antenna_r));
        control.addChild(std::move(eyeball_l));
        control.addChild(std::move(eyeball_r));

        auto head_m = Group(glm::translate(glm::vec3(0.0f, 1.2f, 0.0f)));
        auto control_t = head_m.addChild(std::move(control));
        root.addChild(std::move(head_m));

        return &control_t->transform;
    }

    std::tuple<Transform *, Transform *> initArms(Group &root, std::shared_ptr<Material> material) {
        auto arm = Mesh::fromObjFile("meshes/Robot-parts-2018/limb_s.obj");
        arm.transform.model = glm::translate(glm::vec3(0.0f, -0.8f, 0.0f)) * glm::scale(glm::vec3(1.0f, 2.0f, 1.0f));
        arm.material = material;

        auto arm_l = Group();
        arm_l.addChild(arm);
        auto arm_l_b = Group(glm::translate(glm::vec3(-1.4f, 0.6f, 0.0f)));
        auto left_t = arm_l_b.addChild(std::move(arm_l));

        auto arm_r = Group();
        arm_r.addChild(std::move(arm));
        auto arm_r_b = Group(glm::translate(glm::vec3(1.4f, 0.6f, 0.0f)));
        auto right_t = arm_r_b.addChild(std::move(arm_r));

        root.addChild(std::move(arm_l_b));
        root.addChild(std::move(arm_r_b));

        return std::make_tuple(&left_t->transform, &right_t->transform);
    }

    std::tuple<Transform *, Transform *> initLegs(Group &root, std::shared_ptr<Material> material) {
        auto limb = Mesh::fromObjFile("meshes/Robot-parts-2018/limb_s.obj");
        limb.material = material;

        auto leg = Group(glm::translate(glm::vec3(0.0f, -0.7f, 0.0f)));
        leg.addChild(std::make_unique<Mesh>(limb));

        auto leg_l = Group();
        leg_l.addChild(leg);
        auto leg_l_m = Group(glm::translate(glm::vec3(-0.5f, -1.0f, 0.0f)));
        auto left_t = leg_l_m.addChild(std::move(leg_l));

        auto leg_r = Group();
        leg_r.addChild(std::move(leg));
        auto leg_r_m = Group(glm::translate(glm::vec3(0.5f, -1.0f, 0.0f)));
        auto right_t = leg_r_m.addChild(std::move(leg_r));

        root.addChild(std::move(leg_l_m));
        root.addChild(std::move(leg_r_m));

        return std::make_tuple(&left_t->transform, &right_t->transform);
    }
}

Group robot(std::shared_ptr<Material> material) {
    Group root;

    auto body = std::make_unique<Mesh>(Mesh::fromObjFile("meshes/Robot-parts-2018/body_s.obj"));
    body->material = material;
    root.addChild(std::move(body));

    initHead(root, material);
    initArms(root, material);
    initLegs(root, material);

    return root;
}
