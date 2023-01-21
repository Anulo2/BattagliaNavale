#ifndef SUPPORT_H
#define SUPPORT_H

#include "MovableUnit.h"

class Support : public MovableUnit {
   public:
    Support(const Position &iBow, const Position &iStern);
    void move(const Position &iTarget, std::shared_ptr<Unit> unitsMatrix[12][12]);
    ~Support();
};

#endif