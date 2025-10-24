#ifndef ATOMINSTANCE_H
#define ATOMINSTANCE_H
#include <Qt>
//TODO: internalize this in the AtomItem class, remove rotation

struct AtomInstance
{
    qreal x;
    qreal y;
    qreal rotation;
    int atomicNumber;
    bool topBonded;
    bool rightBonded;
    bool bottomBonded;
    bool leftBonded;
};

#endif
