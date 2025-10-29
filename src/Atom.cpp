#include "Atom.h"

bool Atom::canBond(Bond b0,Bond b1)
{
    return (
        (b0 == Covalent && b1 == Covalent)
        || (b0 == Positive && b1 == Negative)
        || (b0 == Negative && b1 == Positive)
        );
}

Atom::Atom(
    int atomicNumber
    ,qreal mass
    ,const QColor& color
    ,Bond topBond
    ,Bond rightBond
    ,Bond bottomBond
    ,Bond leftBond
    ):
    _topBond(topBond)
    ,_rightBond(rightBond)
    ,_bottomBond(bottomBond)
    ,_leftBond(leftBond)
    ,_color(color)
    ,_atomicNumber(atomicNumber)
    ,_mass(mass)
{
    Q_ASSERT(atomicNumber >= 1);
}

int Atom::charge() const
{
    return (
        (_topBond == Covalent ? 0 : _topBond == Positive ? 1 : -1)
        +(_rightBond == Covalent ? 0 : _rightBond == Positive ? 1 : -1)
        +(_bottomBond == Covalent ? 0 : _bottomBond == Positive ? 1 : -1)
        +(_leftBond == Covalent ? 0 : _leftBond == Positive ? 1 : -1)
        );
}
