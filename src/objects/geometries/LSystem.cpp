//
//  LSystem.cpp
//  CSE-167-FinalTester
//
//  Created by Wei Zeng on 12/2/19.
//  Copyright © 2019 Wei Zeng. All rights reserved.
//

#include <glm/gtx/rotate_vector.hpp>
#include <string>
#include <random>
#include <chrono>

#include "LSystem.h"
#include "../../gl_wraps/Shader.h"
#include "../Camera.h"
#include "../../materials/Material.h"
#include "../../gl_wraps/GLBuffer.h"
#include "../../gl_wraps/GLVertexArray.h"

std::default_random_engine rand_eng;
std::uniform_int_distribution dist(0, 3);

LSystem::LSystem(float step_size, float angle_increment, std::string rules, int iteration) {
    this->position = glm::vec3(0, 0, 0);
    this->heading = glm::vec3(0, 1, 0);
    this->step_size = step_size;
    this->angle_increment = angle_increment;
    this->rules = rules;

    vao = std::make_shared<GLVertexArray>();

    auto now = std::chrono::system_clock::now();
    rand_eng.seed(now.time_since_epoch().count());

    genRule(rules, iteration);
    readRules();
}

void LSystem::push() {
    std::tuple<glm::vec3, glm::vec3> input(position, heading);
    stack.push(input);
}

void LSystem::pop() {
    std::tuple<glm::vec3, glm::vec3> out = stack.top();
    position = std::get<0>(out);
    heading = std::get<1>(out);
    stack.pop();
}

void LSystem::draw(const glm::mat4 &world, const Camera &camera) {
    auto &shader = material->setUp();
    camera.setUniform(shader);
    shader.setUniform("model", world * transform.model);

    // Bind to the VAO.
    vao->bind();

    // Draw triangles
    glDrawArrays(GL_LINES, 0, data.size());
    // Unbind from the VAO.
    glBindVertexArray(0);

    material->tearDown();
}

void LSystem::rotX() {
//    std::cerr << "rotate x" << std::endl;
    heading = glm::normalize(glm::rotateX(heading, angle_increment));
//    std::cerr << "heading after rotX: " << glm::to_string(heading) << std::endl;
}

void LSystem::rotY() {
//    std::cerr << "rotate y" << std::endl;
    heading = glm::normalize(glm::rotateY(heading, angle_increment));
//    std::cerr << "heading after rotY: " << glm::to_string(heading) << std::endl;
}

void LSystem::rotZ() {
//    std::cerr << "rotate z" << std::endl;
    heading = glm::normalize(glm::rotateZ(heading, angle_increment));
//    std::cerr << "heading after rotZ: " << glm::to_string(heading) << std::endl;
}

void LSystem::forward() {
//    std::cerr << "forwarding" << std::endl;
//    points.push_back(points.at(points.size() - 1) + heading * step_size);

    data.push_back(position);
    position = position + heading * step_size;
    data.push_back(position);

//    std::cerr << "values in data: " << glm::to_string(data.at(0)) << " + " << glm::to_string(data.at(1)) << std::endl;
}

void LSystem::readRules() {
    points.push_back(position);

    std::string cmpstr;
//    std::cerr << "reading rules" << std::endl;

    for (int i = 0; i < generatedString.length(); i++) {
        cmpstr = generatedString.at(i);
        if (cmpstr.compare("F") == 0) {
            forward();
        } else if (cmpstr.compare("[") == 0) {
            push();
        } else if (cmpstr.compare("]") == 0) {
            pop();
        } else if (cmpstr.compare("X") == 0) {
            rotX();
        } else if (cmpstr.compare("Y") == 0) {
            rotY();
        } else if (cmpstr.compare("Z") == 0) {
            rotZ();
        } else if (cmpstr.compare("-") == 0) {
            angle_increment = -angle_increment;
        } else if (cmpstr.compare("+") == 0) {
            angle_increment = abs(angle_increment);
        } else {
            leaf_pos.push_back(position);
        }
    }

    const auto inf = std::numeric_limits<float>::infinity();
    glm::vec3 minVal(inf, inf, inf), maxVal(-inf, -inf, -inf);
    for (auto &v : data) {
        minVal = glm::min(minVal, v);
        maxVal = glm::max(maxVal, v);
    }
    bb = {minVal, maxVal};

    GLBuffer vbo;

    // Bind to the VAO.
    vao->bind();
    // Bind to the first VBO. We will use it to store the points.
    vbo.bind(GL_ARRAY_BUFFER);
    // Pass in the data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * data.size(),
                 data.data(), GL_STATIC_DRAW);
    // Enable vertex attribute 0.
    // We will be able to access points through it.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    // Unbind from the VBO.
    vbo.unbind();
    // Unbind from the VAO.
    vao->unbind();

    points.clear();
}

void LSystem::genRule(std::string sentence, int depth) {
    if (depth == 0) {
//        std::cerr << "generated string: " << sentence << std::endl;
        generatedString = sentence;
        return;
    }

    std::string nextSentence;

    for (int i = 0; i < sentence.length(); i++) {
        if (sentence[i] == 'A') {
            int choice = dist(rand_eng);
            if (choice == 0)
                nextSentence += "F[[+ZFA]-ZFA][[+XFA]-XFA]";
            else if (choice == 1)
                nextSentence += "F[[-ZFA]+ZFA][[+YFA]-YFA]";
            else if (choice == 2)
                nextSentence += "F[[+XFA]-XFA][[+YFA]-YFA]";
            else if (choice == 3)
                nextSentence += "F[[+ZFA]-ZFA][[+XFA]-XFA]";
            continue;
        }
        if (sentence[i] == 'F') {
            nextSentence += "F";
            continue;
        }
        nextSentence += sentence[i];
    }
    genRule(nextSentence, depth - 1);
}
