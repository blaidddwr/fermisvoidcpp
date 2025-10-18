#include "AtomItem.h"
#include "AtomRenderer.h"
#include "Atoms.h"

AtomItem::AtomItem(PortalItem *parent)
    : OpenGLItem{parent}
{}

void AtomItem::setAtom(int atomicNumber)
{
    if (atomicNumber == -1)
    {
        _atoms.set() = {};
        setRadius(0.0);
    }
    else
    {
        Q_ASSERT(atomicNumber > 0);
        Q_ASSERT(atomicNumber <= Atoms::instance().size());
        _atoms.set() = {{0,0,0,atomicNumber,false,false,false,false}};
        setRadius(0.8);
    }
}

OpenGLRenderer* AtomItem::_createRenderer() const
{
    return new AtomRenderer();
}

void AtomItem::_sync(OpenGLRenderer* renderer)
{
    auto ar = qobject_cast<AtomRenderer*>(renderer);
    Q_ASSERT(ar);
    if (_atoms.updated()) ar->setAtoms(_atoms.get());
}

void AtomItem::setRadius(qreal value)
{
    if (_radius != value)
    {
        _radius = value;
        emit radiusChanged(value);
    }
}
