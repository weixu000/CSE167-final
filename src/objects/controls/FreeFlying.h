#ifndef FREEFLYING_H
#define FREEFLYING_H

#include "FreeMover.h"
#include "FreeRotator.h"

class FreeFlying : public FreeMover, public FreeRotator {
public:
    using FreeMover::FreeMover;

protected:
    NodePtr clone() override { return std::make_unique<FreeFlying>(*this); }
};


#endif //FREEFLYING_H
