#ifndef ATOMINSTANCE_H
#define ATOMINSTANCE_H

struct AtomInstance
{
    int x;
    int y;
    float rotation;
    int atomicNumber;
    bool topBonded;
    bool rightBonded;
    bool bottomBonded;
    bool leftBonded;
};

#endif
