#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include "Unit.h"

class Battleship : public Unit {
public:
    Battleship(const Position &iBow, const Position &iStern);
    void move(const Position &iTarget, std::shared_ptr<Unit> unitsMatrix[12][12]);
    ~Battleship();
};

#endif