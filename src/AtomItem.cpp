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
        _atoms.set() = {{{0,0},atomicNumber}};
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
    _atoms.set() = molecule.atoms();
    setRadius(molecule.radius()+0.8);
    setScale((molecule.radius()+0.8)/0.8);
    setOffset(molecule.center());
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
