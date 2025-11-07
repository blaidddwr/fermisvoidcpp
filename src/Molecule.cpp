#include "Atom.h"
#include "Atoms.h"
#include "Molecule.h"
#include <QSet>

Molecule::Molecule(int atomicNumber)
{
    Q_ASSERT(atomicNumber > 0);
    Q_ASSERT(atomicNumber <= Atoms::instance().size());
    addAtom({0,0},atomicNumber);
}

Molecule::Molecule(Molecule&& other):
    _atoms(std::move(other._atoms))
    ,_freezingPoint(other._freezingPoint)
    ,_molarMass(other._molarMass)
{
    other._freezingPoint = 0.0;
    other._molarMass = 0.0;
}

Molecule& Molecule::operator=(Molecule&& other)
{
    _atoms = std::move(other._atoms);
    _freezingPoint = other._freezingPoint;
    _molarMass = other._molarMass;
    other._freezingPoint = 0.0;
    other._molarMass = 0.0;
    return *this;
}

QList<int> Molecule::availableAtoms(const QPoint& position) const
{
    QList<int> ret;
    auto top = atom({position.x(),position.y()+1});
    auto right = atom({position.x()+1,position.y()});
    auto bottom = atom({position.x(),position.y()-1});
    auto left = atom({position.x()-1,position.y()});
    auto& atoms = Atoms::instance();
    for (int a = 1;a <= atoms.size();a++)
    {
        if (
            atoms.canBond(a,top,Atoms::Direction::Top)
            && atoms.canBond(a,right,Atoms::Direction::Right)
            && atoms.canBond(a,bottom,Atoms::Direction::Bottom)
            && atoms.canBond(a,left,Atoms::Direction::Left)
            )
        {
            ret.append(a);
        }
    }
    return ret;
}

QList<QPoint> Molecule::availablePositions() const
{
    QSet<QPoint> ret;
    const auto ps = positions();
    if (ps.isEmpty()) ret.insert({0,0});
    for (auto pos: ps)
    {
        if (!ps.contains({pos.x(),pos.y()+1})) ret.insert({pos.x(),pos.y()+1});
        if (!ps.contains({pos.x()+1,pos.y()})) ret.insert({pos.x()+1,pos.y()});
        if (!ps.contains({pos.x(),pos.y()-1})) ret.insert({pos.x(),pos.y()-1});
        if (!ps.contains({pos.x()-1,pos.y()})) ret.insert({pos.x()-1,pos.y()});
    }
    return ret.values();
}

bool Molecule::addAtom(const QPoint& position,int atomicNumber)
{
    if (!canAddAtom(position,atomicNumber)) return false;
    _atoms.insert(position,atomicNumber);
    _molarMass += Atoms::instance().get(atomicNumber).mass();
    update();
    return true;
}

bool Molecule::canAddAtom(const QPoint& position,int atomicNumber) const
{
    if (_atoms.contains(position)) return false;
    auto top = atom({position.x(),position.y()+1});
    auto right = atom({position.x()+1,position.y()});
    auto bottom = atom({position.x(),position.y()-1});
    auto left = atom({position.x()-1,position.y()});
    auto& atoms = Atoms::instance();
    return (
        atoms.canBond(atomicNumber,top,Atoms::Direction::Top)
        && atoms.canBond(atomicNumber,right,Atoms::Direction::Right)
        && atoms.canBond(atomicNumber,bottom,Atoms::Direction::Bottom)
        && atoms.canBond(atomicNumber,left,Atoms::Direction::Left)
        );
}

void Molecule::update()
{
    qreal x = 0.0;
    qreal y = 0.0;
    for (const auto& pos: _atoms.keys())
    {
        x += qreal(pos.x())/qreal(_atoms.size());
        y += qreal(pos.y())/qreal(_atoms.size());
    }
    _center = {x,y};
    _radius = 0.0;
    for (const auto& pos: _atoms.keys())
    {
        _radius = fmax(_radius,(pos.x()*pos.x())+(pos.y()*pos.y()));
    }
    _radius = sqrt(_radius);
    _freezingPoint = FreezingPointA+(FreezingPointB*_molarMass);
}
