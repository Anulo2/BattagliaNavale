#ifndef ENTITY_H
#define ENTITY_H

#include <ostream>

#include "Position.h"

class Entity {
public:
    Entity();
    Entity(const Position & iPos, const char &iId);
    // Entity(const Entity &a);
    void updatePos(const Position &iPos);
    Position getPos() const;
    char getId() const;
    void setId(const char &iId);
    ~Entity();
private:
    char id = ' ';
    Position pos;
};
std::ostream &operator<<(std::ostream &os, Entity &a);
std::ostream &operator<<(std::ostream &os, Entity *a);
bool operator==(Entity a, Entity b);
bool operator!=(Entity a, Entity b);
#endif