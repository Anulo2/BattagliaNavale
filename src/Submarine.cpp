#include "Submarine.h"

Submarine::Submarine(const Position &iBow, const Position &iStern)
    : MovableUnit(iBow, iStern, 1, 1, 'E'){};

Submarine::~Submarine() {
}