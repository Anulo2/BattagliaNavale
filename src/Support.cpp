#include "Support.h"

Support::Support(const Position &iBow, const Position &iStern)
    : MovableUnit(iBow, iStern, 3, 3, 'S'){};

void Support::move(const Position &iTarget, std::shared_ptr<Unit> unitsMatrix[12][12]) {
    std::cout << "here\n";
    MovableUnit::move(iTarget, unitsMatrix);
    for (int i = -1; i < 1; i++) {
        for (int j = -1; j < 1; j++) {
            if ((iTarget.getIntY() + i) <= 12 && (iTarget.getIntY() + i) >= 1 && (iTarget.getX() + i) <= 12 && (iTarget.getX() + i) >= 1) {
                if (unitsMatrix[iTarget.getIntY() + i - 1][iTarget.getX() + j - 1] && unitsMatrix[iTarget.getIntY() + i - 1][iTarget.getX() + j - 1]->getMiddle() != this->getMiddle()) {
                    unitsMatrix[iTarget.getIntY() + i - 1][iTarget.getX() + j - 1]->heal();
                    std::cout << "here, healing\n";
                }
            }
        }
    }
}

Support::~Support() {
}