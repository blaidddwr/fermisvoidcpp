#include "Atom.h"

bool Atom::canBond(Bond b0,Bond b1)
{
    return (
        (b0 == Bond::Covalent && b1 == Bond::Covalent)
        || (b0 == Bond::Positive && b1 == Bond::Negative)
        || (b0 == Bond::Negative && b1 == Bond::Positive)
        );
}

Atom::Direction Atom::direction(int index)
{
    Q_ASSERT(index >= 0);
    Q_ASSERT(index < 4);
    return static_cast<Direction>(index);
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
    _bonds{topBond,rightBond,bottomBond,leftBond}
    ,_color(color)
    ,_atomicNumber(atomicNumber)
    ,_mass(mass)
{
    Q_ASSERT(atomicNumber >= 1);
}

Atom::Bond Atom::bond(Direction d) const
{
    return _bonds[static_cast<int>(d)];
}

int Atom::charge() const
{
    int ret = 0;
    for (int i = 0;i < 4;i++)
    {
        ret += _bonds[i] == Bond::Covalent ? 0 : _bonds[i] == Bond::Positive ? 1 : -1;
    }
    return ret;
}
