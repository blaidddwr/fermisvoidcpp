#ifndef ATOMINSTANCE_H
#define ATOMINSTANCE_H
#include <Qt>

struct AtomInstance
{
    int x;
    int y;
    qreal rotation;
    int atomicNumber;
    bool topBonded;
    bool rightBonded;
    bool bottomBonded;
    bool leftBonded;
};

#endif
