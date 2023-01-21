#include "Unit.h"

Unit::Unit(const Position &iBow, const Position &iStern, const int &iDimension,
           const int &iArmor, const char &iId) {
    if (!iBow.isAligned(iStern)) {
        throw std::invalid_argument("Positions must be aligned \n");
    }
    if ((iBow.distanceTo(iStern) + 1) != iDimension) {
        throw std::invalid_argument(
            "These positions do not rapresent that Unit \n");
    }

    vertical = (iBow.getX() == iStern.getX()) ? true : false;
    dimension = iDimension;
    armor = iArmor;
    id = iId;

    Position stern = (iBow < iStern) ? iBow : iStern;

    for (int i = 0; i < iDimension; i++) {
        Position bufferPos;
        if (vertical) {
            bufferPos.setX(iBow.getX());
            bufferPos.setY(stern.getIntY() + i);
        } else {
            bufferPos.setX(stern.getX() + i);
            bufferPos.setY(iBow.getIntY());
        }
        unitSections.push_back(UnitSection(bufferPos, iId));
    }
};
Unit::Unit(const Unit &a) {
    unitSections = a.getUnitSections();
    vertical = a.isVertical();
    dimension = a.getDimension();
    armor = a.getArmor();
    id = a.getId();
};
bool Unit::isHitAt(const Position &iPos) {
    if (Unit::containsPos(iPos)) {
        if (vertical) {
            return unitSections[iPos.getIntY() - Unit::getStern().getIntY()]
                .isAlive();
            // return status[dimension - (Unit::getBow().getIntY() -
            // iPos.getIntY()) - 1];
        } else {
            return unitSections[iPos.getX() - Unit::getStern().getX()]
                .isAlive();
        }
    }
    return false;
}
Position Unit::getMiddle() const {
    return unitSections[dimension / 2].getPos();
};

bool Unit::isVertical() const { return vertical; };

bool Unit::containsPos(const Position &iPos) {
    return iPos.isInside(Unit::getStern(), Unit::getBow());
};
char Unit::getId() const { return id; };
Position Unit::getBow() const {
    if (vertical) {
        return Position(Unit::getMiddle().getX(),
                        Unit::getMiddle().getIntY() + dimension / 2);
    } else {
        return Position(Unit::getMiddle().getX() + dimension / 2,
                        Unit::getMiddle().getIntY());
    }
};
Position Unit::getStern() const {
    if (vertical) {
        return Position(Unit::getMiddle().getX(),
                        Unit::getMiddle().getIntY() - (dimension / 2));
    } else {
        return Position(Unit::getMiddle().getX() - (dimension / 2),
                        Unit::getMiddle().getIntY());
    }
};
int Unit::getArmor() const { return armor; }
int Unit::getDimension() const { return dimension; }
void Unit::damage(const Position &iTarget) {
    unitSections[Unit::getStern().distanceTo(iTarget)].hit();
}
void Unit::setMiddle(const Position &iPos,
                     std::shared_ptr<Unit> unitsMatrix[12][12]) {
    Position middle = Unit::getMiddle();
    if (middle == iPos) {
        return;
    }
    bool smaller = iPos < middle;
    int x1, y1, x2, y2 = 0;
    int offset = (int)(unitSections.size() / 2);
    x1 = iPos.getX();
    y1 = iPos.getIntY();
    x2 = middle.getX();
    y2 = middle.getIntY();
    int j = smaller ? 0 : unitSections.size();
    for (int i = 0; i < unitSections.size(); i++) {
        if (vertical) {
            if (smaller) {
                y1 = iPos.getIntY() - offset + i;
                y2 = middle.getIntY() - offset + i;
            } else {
                y1 = iPos.getIntY() + offset - i;
                y2 = middle.getIntY() + offset - i;
            }
        } else {
            if (smaller) {
                x1 = iPos.getX() - offset + i;
                x2 = middle.getX() - offset + i;
            } else {
                x1 = iPos.getX() + offset - i;
                x2 = middle.getX() + offset - i;
            }
        }
        std::cout << x2 << ", " << y2 << std::endl;
        std::cout << x1 << ", " << y1 << std::endl;
        unitsMatrix[y1 - 1][x1 - 1] = unitsMatrix[y2 - 1][x2 - 1];
        unitsMatrix[y2 - 1][x2 - 1] = nullptr;
        unitSections[j].updatePos(Position(x1, y1));
        j = smaller ? j + 1 : j - 1;
    }
}
void Unit::heal() {
    if (armor != 0) {
        for (auto unit : unitSections) {
            unit.restore();
            std::cout << "restoring\n";
        }
        armor = dimension;
    } else {
        throw std::invalid_argument("The unit is dead!");
    }
}
bool Unit::isDead() const { return (armor == 0); }
std::vector<UnitSection> Unit::getUnitSections() const { return unitSections; }

void Unit::move(const Position &iTarget,
                std::shared_ptr<Unit> unitsMatrix[12][12]) {}

Unit::~Unit() {}

std::ostream &operator<<(std::ostream &os, Unit &a) {
    std::string status;
    std::vector<UnitSection> sections = a.getUnitSections();
    for (int i = 0; i < sections.size(); i++) {
        status.push_back(sections[i].isAlive() ? (a.getId()) : a.getId() + 32);
    }
    os << "(Pos: " << a.getMiddle() << ", Dim: " << a.getDimension();
    os << ", Vert: " << a.isVertical() << ", Armor: " << a.getArmor()
       << ", Status: " << status << ", Id: " << a.getId() << ")";
    return os;
}
std::ostream &operator<<(std::ostream &os, Unit *a) {
    os << *a;
    return os;
}
