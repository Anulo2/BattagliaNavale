#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <ostream>
#include <memory>
#include <vector>
#include "Entity.h"
#include "Unit.h"
#include "Battleship.h"
#include "MovableUnit.h"
#include "Submarine.h"
#include "Support.h"

class Controller {
public:
    Controller(const bool & isFirstPlayer);
    std::vector<Entity> action(const char &type, const Position & iSource, const Position & iTarget);
    void mergeEntities(std::vector<Entity> iEnemyEntities);
    bool isDead();
    void addUnit(const char &type, const Position &iStern, const Position & iBow);
    
    bool checkUnitPlacement(std::shared_ptr<Unit> initialUnit,const Position & a, const Position &b) const;
    void print(std::ostream &os);
~Controller();
private:
    void removeDeadUnits();
    std::vector<std::shared_ptr<Unit>> units;
    std::vector<std::shared_ptr<Entity>> enemyEntities;
    std::shared_ptr<Entity> enemyEntitiesMatrix[12][12];
    std::shared_ptr<Unit> unitsMatrix[12][12];
    bool dead = false;
    bool listeningForActions;
};


std::ostream &operator<<(std::ostream &os, Controller &a);
std::ostream &operator<<(std::ostream &os, Controller *a);

#endif