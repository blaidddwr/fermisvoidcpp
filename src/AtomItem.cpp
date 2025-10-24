#include "AtomItem.h"
#include "AtomRenderer.h"
#include "Atoms.h"
#include "Molecule.h"

AtomItem::AtomItem(PortalItem *parent)
    : OpenGLItem{parent}
{}

void AtomItem::setAtom(int atomicNumber)
{
    if (atomicNumber == -1)
    {
        _atoms.set() = {};
        setRadius(0.0);
        setScale(1.0);
        setOffset({0.0,0.0});
    }
    else
    {
        Q_ASSERT(atomicNumber > 0);
        Q_ASSERT(atomicNumber <= Atoms::instance().size());
        _atoms.set() = {{0,0,0,atomicNumber,false,false,false,false}};
        setRadius(0.8);
        setScale(1.0);
        setOffset({0.0,0.0});
    }
}

void AtomItem::setMolecule(const Molecule& molecule)
{
    if (molecule.isEmpty())
    {
        setAtom(-1);
        return;
    }
    QList<AtomInstance> atoms;
    const auto posns = molecule.positions();
    qreal x = 0.0;
    qreal y = 0.0;
    for (auto pos: posns)
    {
        x += qreal(pos.x())/qreal(posns.size());
        y += qreal(pos.y())/qreal(posns.size());
        atoms.append(
            {
                qreal(pos.x())
                ,qreal(pos.y())
                ,0.0
                ,molecule.atom(pos)
                ,posns.contains({pos.x(),pos.y()+1})
                ,posns.contains({pos.x()+1,pos.y()})
                ,posns.contains({pos.x(),pos.y()-1})
                ,posns.contains({pos.x()-1,pos.y()})
            }
        );
    }
    qreal distance = 0.0;
    for (auto& a: atoms)
    {
        a.x -= x;
        a.y -= y;
        distance = fmax(distance,(a.x*a.x)+(a.y*a.y));
    }
    distance = sqrt(distance);
    _atoms.set() = atoms;
    setRadius(distance+0.8);
    setScale(0.8/(distance+0.8));
    setOffset({0.0,0.0});
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
