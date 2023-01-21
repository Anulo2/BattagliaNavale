#include "Battleship.h"

Battleship::Battleship(const Position &iBow, const Position &iStern)
    : Unit(iBow, iStern, 5, 5, 'C'){};
void Battleship::move(const Position &iTarget, std::shared_ptr<Unit> unitsMatrix[12][12]){
    return;
}
Battleship::~Battleship(){
    
}