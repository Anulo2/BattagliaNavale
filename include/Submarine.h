#ifndef SUBMARINE_H
#define SUBMARINE_H

#include "MovableUnit.h"

class Submarine : public MovableUnit {
public:
    Submarine(const Position &iBow, const Position &iStern);
    ~Submarine();
};

#endif