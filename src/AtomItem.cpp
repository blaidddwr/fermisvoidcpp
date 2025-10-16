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
        setRadius(0.0);
    }
    else
    {
        _atoms.set() = {{0,0,0,atomicNumber,false,false,false,false}};
        setRadius(0.8);
    }
}

void AtomItem::setRadius(qreal value)
{
    if (_radius != value)
    {
        _radius = value;
        emit radiusChanged(value);
    }
}
