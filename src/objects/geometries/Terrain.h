#ifndef TERRAIN_H
#define TERRAIN_H

#include "Wireframe.h"

class Terrain : public Wireframe {
public:
    Terrain(int n, const std::array<float, 4> &corners);

protected:
    NodePtr clone() override { return std::make_unique<Terrain>(*this); }

private:
    using HeightMap = std::vector<std::vector<float>>;

    static HeightMap diamondSquare(int n, const std::array<float, 4> &corners);
};


#endif //TERRAIN_H
