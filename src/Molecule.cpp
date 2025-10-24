#include "Atom.h"
#include "Atoms.h"
#include "Molecule.h"
#include <QSet>
#include <random>

Molecule Molecule::generate()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    auto& atoms = Atoms::instance();
    std::bernoulli_distribution nextAtom(0.5);
    int i = 1;
    while (nextAtom(gen))
    {
        if (i == (atoms.size())) break;
        i++;
    }
    Molecule ret(i);
    while (ret.freezingPoint() < 4000.0)
    {
        auto aposns = ret.availablePositions();
        if (!aposns.isEmpty())
        {
            auto pos = aposns.at(std::uniform_int_distribution<>(0,aposns.size()-1)(gen));
            auto aas = ret.availableAtoms(pos);
            if (!aas.isEmpty())
            {
                int i = 0;
                while (nextAtom(gen))
                {
                    if (i == (aas.size()-1)) break;
                    i++;
                }
                auto an = aas.at(i);
                ret.addAtom(pos,an);
            }
        }
    }
    return ret;
}

Molecule::Molecule(int atomicNumber)
{
    Q_ASSERT(atomicNumber > 0);
    Q_ASSERT(atomicNumber <= Atoms::instance().size());
    addAtom({0,0},atomicNumber);
}

Molecule::Molecule(Molecule&& other):
    _atoms(std::move(other._atoms))
    ,_freezingPoint(other._freezingPoint)
    ,_liquidSlope(other._liquidSlope)
    ,_molarMass(other._molarMass)
{
    other._freezingPoint = 0.0;
    other._liquidSlope = 0.0;
    other._molarMass = 0.0;
}

Molecule& Molecule::operator=(Molecule&& other)
{
    _atoms = std::move(other._atoms);
    _freezingPoint = other._freezingPoint;
    _liquidSlope = other._liquidSlope;
    _molarMass = other._molarMass;
    other._freezingPoint = 0.0;
    other._liquidSlope = 0.0;
    other._molarMass = 0.0;
    return *this;
}

QHash<int,int> Molecule::atoms() const
{
    QHash<int,int> ret;
    for (auto an: _atoms.values())
    {
        if (!ret.contains(an)) ret.insert(an,0);
        ret[an]++;
    }
    return ret;
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
    const auto posns = positions();
    for (auto pos: posns)
    {
        if (!posns.contains({pos.x(),pos.y()+1})) ret.insert({pos.x(),pos.y()+1});
        if (!posns.contains({pos.x()+1,pos.y()})) ret.insert({pos.x()+1,pos.y()});
        if (!posns.contains({pos.x(),pos.y()-1})) ret.insert({pos.x(),pos.y()-1});
        if (!posns.contains({pos.x()-1,pos.y()})) ret.insert({pos.x()-1,pos.y()});
    }
    return ret.values();
}

bool Molecule::addAtom(const QPoint& position,int atomicNumber)
{
    if (_atoms.contains(position)) return false;
    auto top = atom({position.x(),position.y()+1});
    auto right = atom({position.x()+1,position.y()});
    auto bottom = atom({position.x(),position.y()-1});
    auto left = atom({position.x()-1,position.y()});
    auto& atoms = Atoms::instance();
    if (
        !atoms.canBond(atomicNumber,top,Atoms::Direction::Top)
        || !atoms.canBond(atomicNumber,right,Atoms::Direction::Right)
        || !atoms.canBond(atomicNumber,bottom,Atoms::Direction::Bottom)
        || !atoms.canBond(atomicNumber,left,Atoms::Direction::Left)
        )
    {
        return false;
    }
    _atoms.insert(position,atomicNumber);
    _molarMass += atoms.get(atomicNumber).mass();
    update();
    return true;
}

void Molecule::update()
{
    _freezingPoint = FreezingPointA+(FreezingPointB*_molarMass);
    //TODO: liquid slope
}
