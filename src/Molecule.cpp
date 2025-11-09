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
    auto i = _atoms.find(position);
    if (i == _atoms.end()) _atoms.insert(position,atomicNumber);
    else
    {
        _molarMass -= Atoms::instance().get(i.value()).mass();
        i.value() = atomicNumber;
    }
    _molarMass += Atoms::instance().get(atomicNumber).mass();
    update();
    return true;
}

bool Molecule::canAddAtom(const QPoint& position,int atomicNumber) const
{
    if (_atoms.contains(position)) return true;
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

bool Molecule::canRemoveAtom(const QPoint& position) const
{
    if (
        !_atoms.contains(position)
        || position == QPoint(0,0)
        )
    {
        return false;
    }
    QSet<QPoint> travelled {position};
    std::function<void(const QPoint&)> travel;
    travel = [&travel,this,&travelled](const QPoint& pos)
    {
        if (
            _atoms.contains(pos)
            && !travelled.contains(pos)
            )
        {
            travelled.insert(pos);
            travel({pos.x(),pos.y()+1});
            travel({pos.x()+1,pos.y()});
            travel({pos.x(),pos.y()-1});
            travel({pos.x()-1,pos.y()});
        }
    };
    const QList<QPoint> ss {
        {position.x(),position.y()+1}
        ,{position.x()+1,position.y()}
        ,{position.x(),position.y()-1}
        ,{position.x()-1,position.y()}
    };
    for (const auto& pos: ss)
    {
        if (_atoms.contains(pos))
        {
            travel(pos);
            return travelled.size() == _atoms.size();
        }
    }
    return false;
}

bool Molecule::removeAtom(const QPoint& position)
{
    if (!canRemoveAtom(position)) return false;
    auto i = _atoms.find(position);
    Q_ASSERT(i != _atoms.end());
    _molarMass += Atoms::instance().get(i.value()).mass();
    _atoms.erase(i);
    update();
    return true;
}

void Molecule::update()
{
    _radius = 0.0;
    for (const auto& pos: _atoms.keys())
    {
        _radius = fmax(_radius,(pos.x()*pos.x())+(pos.y()*pos.y()));
    }
    _radius = sqrt(_radius);
    _freezingPoint = FreezingPointA+(FreezingPointB*_molarMass);
}
