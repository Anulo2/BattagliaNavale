#ifndef MOVABLEUNIT_H
#define MOVABLEUNIT_H

#include "Unit.h"

class MovableUnit : public Unit {
public:
    MovableUnit(const Position &iBow, const Position &iStern,const int &iDimension, const int &iArmor, const char & iId);
    void move(const Position &iTarget, std::shared_ptr<Unit> unitsMatrix[12][12]);
    ~MovableUnit();
};

#endif