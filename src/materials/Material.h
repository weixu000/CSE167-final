#ifndef MATERIAL_H
#define MATERIAL_H

class Shader;

class Material {
public:
    virtual Shader &setUp() const = 0;

    virtual void tearDown() const = 0;
};


#endif //MATERIAL_H
