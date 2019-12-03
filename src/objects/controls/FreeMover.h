#ifndef FREEMOVER_H
#define FREEMOVER_H

#include "../Group.h"

class FreeMover : virtual public Group {
public:
    using Group::Group;

    void update() override;

    bool forward = false, left = false, backward = false, right = false, up = false, down = false;

protected:
    NodePtr clone() override { return std::make_unique<FreeMover>(*this); }
};


#endif //FREEMOVER_H
