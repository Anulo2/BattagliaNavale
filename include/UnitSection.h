#ifndef UNITSECTION_H
#define UNITSECTION_H
#include <iostream>
#include <memory>
#include <vector>
#include <ostream>
#include "Position.h"
#include "Entity.h"

class UnitSection: public Entity {
    public:
        UnitSection(const Position &iPos, const char & iId);
        bool isAlive() const;
        void hit();
        void restore();
        ~UnitSection();
    protected:
        bool alive = true;

};

std::ostream &operator<<(std::ostream &os, UnitSection *a);
std::ostream &operator<<(std::ostream &os, UnitSection &a);

#endif