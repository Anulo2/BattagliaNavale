#include "MovableUnit.h"

MovableUnit::MovableUnit(const Position &iBow, const Position &iStern,const int &iDimension, const int &iArmor, const char & iId)
    : Unit(iBow, iStern, iDimension, iArmor, iId){};

void MovableUnit::move(const Position &iTarget, std::shared_ptr<Unit> unitsMatrix[12][12]){
    setMiddle(iTarget, unitsMatrix);
}
MovableUnit::~MovableUnit(){
        
}