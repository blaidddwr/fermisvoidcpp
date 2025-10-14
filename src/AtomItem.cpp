#include "AtomItem.h"
#include "AtomRenderer.h"

AtomItem::AtomItem(QObject *parent)
    : QObject{parent}
{}

void AtomItem::sync(AtomRenderer& renderer)
{
    if (_atoms.updated()) renderer.setAtoms(_atoms.get());
}

void AtomItem::setAtom(int atomicNumber)
{
    if (atomicNumber == -1)
    {
        _atoms.set() = {};
        setDesiredWarpRadius(0.0);
    }
    else
    {
        _atoms.set() = {{0,0,0,atomicNumber,false,false,false,false}};
        setDesiredWarpRadius(0.8);
    }
}

void AtomItem::setDesiredWarpRadius(qreal value)
{
    if (_desiredWarpRadius != value)
    {
        _desiredWarpRadius = value;
        emit desiredWarpRadiusChanged(value);
    }
}
