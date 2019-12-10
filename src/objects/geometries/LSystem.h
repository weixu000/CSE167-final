//
//  LSystem.h
//  CSE-167-FinalTester
//
//  Created by Wei Zeng on 12/2/19.
//  Copyright © 2019 Wei Zeng. All rights reserved.
//

#ifndef Lsystem_hpp
#define Lsystem_hpp

#include <glm/glm.hpp>
#include <vector>
#include <tuple>
#include <stack>

#include "Geometry.h"

class GLVertexArray;
class Material;

class LSystem : public Geometry {
private:
    glm::vec3 position;
    glm::vec3 heading;

    float step_size;
    float angle_increment;

    std::stack<std::tuple<glm::vec3, glm::vec3>> stack;
    std::vector<glm::vec3> points;
    std::vector<glm::vec3> leaf_pos;
    std::vector<glm::vec3> data;
    std::string rules, generatedString;

    std::shared_ptr<GLVertexArray> vao;

    void genRule(std::string sentence, int depth);

    void readRules();

    void forward();

    void rotX();

    void rotY();

    void rotZ();

    void push();

    void pop();

    AABB bb;

protected:
    NodePtr clone() override { return std::make_unique<LSystem>(*this); }

public:
    LSystem(float step_size, float angle_increment, std::string rules, int iteration);

    void draw(const glm::mat4 &world, const Camera &camera) override;

    virtual AABB boundingBox() const { return bb; }

    std::shared_ptr<Material> material;
};

#endif /* Lsystem_hpp */
