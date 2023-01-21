#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <ostream>
#include <vector>

// A = 0 ... N = 11
static const char rows[]{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'L', 'M', 'N'};

class Position {
public:
    Position();
    Position(const int &iX, const char &iY);
    Position(const int &iX, const int &iY);
    char getY() const;
    int getX() const;
    int getIntY() const;
    void setX(int iX) { x = iX; };
    void setY(int iY) { y = iY; };
    bool isInside(Position a, Position b) const;
    bool isAligned(const Position &a) const;
    int distanceTo(const Position &a) const;
    bool isSmaller(const Position &a) const;
    std::vector<Position> getPositionsBetween(const Position &a) const;

    ~Position();

private:
    int x;
    int y;
};

bool operator==(const Position &a, const Position &b);
bool operator!=(const Position &a, const Position &b);
bool operator <= (const Position &a, const Position &b);
bool operator >= (const Position &a, const Position &b);
bool operator < (const Position &a, const Position &b);
bool operator > (const Position &a, const Position &b);

std::ostream &operator<<(std::ostream &os, Position a);
std::ostream &operator<<(std::ostream &os, Position *a);

#endif