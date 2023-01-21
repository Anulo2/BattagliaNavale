#include "UnitSection.h"

UnitSection::UnitSection(const Position &iPos, const char &iId) : Entity(iPos, iId){};
bool UnitSection::isAlive() const {
    return alive;
}
void UnitSection::hit() {
    if (alive) {
        setId(getId() + 32);
        alive = false;
    }
}
void UnitSection::restore() {
    if (!alive) {
        std::cout << (char)(getId() - 32) << "\n";
        setId((char)(getId() - 32));
        alive = true;
    }
}
UnitSection::~UnitSection() {
}
std::ostream &operator<<(std::ostream &os, UnitSection &a) {
    os << "(" << a.getPos() << ", " << a.getId() << ", " << a.isAlive() << ")";
    return os;
}
std::ostream &operator<<(std::ostream &os, UnitSection *a) {
    os << *a;
    return os;
}