#ifndef UNIT_H
#define UNIT_H
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

#include "./Position.h"
#include "./UnitSection.h"

class Unit {
   public:
    Unit(const Position &iBow, const Position &iStern, const int &iDimension, const int &iArmor, const char &iId);
    Unit(const Unit &a);
    Position getMiddle() const;
    bool isVertical() const;
    bool containsPos(const Position &iPos);
    char getId() const;
    Position getBow() const;
    Position getStern() const;
    int getArmor() const;
    int getDimension() const;
    void damage(const Position &iTarget);
    void heal();
    bool isDead() const;
    bool isHitAt(const Position &iPos);
    std::vector<UnitSection> getUnitSections() const;
    virtual void move(const Position &iTarget, std::shared_ptr<Unit> unitsMatrix[12][12]);
    ~Unit();

   protected:
    void setMiddle(const Position &iPos, std::shared_ptr<Unit> unitsMatrix[12][12]);
    std::vector<UnitSection> unitSections;
    char id;
    int armor;
    int dimension;
    bool vertical;
};
std::ostream &operator<<(std::ostream &os, Unit &a);
std::ostream &operator<<(std::ostream &os, Unit *a);
#endif