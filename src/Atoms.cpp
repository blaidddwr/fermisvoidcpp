#include "Atom.h"
#include "Atoms.h"
#include <QGuiApplication>
#include <random>

Atoms* Atoms::_instance {nullptr};

Atoms& Atoms::instance()
{
    if (!_instance) _instance = new Atoms;
    return *_instance;
}

bool Atoms::canBond(int atomicNumber0,int atomicNumber1,Direction direction)
{
    if (atomicNumber1 == -1) return true;
    const auto& a0 = get(atomicNumber0);
    const auto& a1 = get(atomicNumber1);
    switch (direction)
    {
    case Direction::Top:
        return Atom::canBond(a0.topBond(),a1.bottomBond());
    case Direction::Right:
        return Atom::canBond(a0.rightBond(),a1.leftBond());
    case Direction::Bottom:
        return Atom::canBond(a0.bottomBond(),a1.topBond());
    case Direction::Left:
        return Atom::canBond(a0.leftBond(),a1.rightBond());
    default:
        return false;
    }
}

const Atom& Atoms::get(int atomicNumber) const
{
    Q_ASSERT(atomicNumber >= 1);
    Q_ASSERT(atomicNumber <= size());
    return *_atoms.at(atomicNumber-1);
}

void Atoms::generateAtoms(int seed)
{
    emit atomsAboutToReset();
    qDeleteAll(_atoms);
    _atoms.clear();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> color {0,255};
    QList<int> bondWeights(3);
    bondWeights[static_cast<int>(Atom::Bond::Positive)] = 45;
    bondWeights[static_cast<int>(Atom::Bond::Negative)] = 45;
    bondWeights[static_cast<int>(Atom::Bond::Covalent)] = 10;
    std::discrete_distribution<> bond(bondWeights.begin(),bondWeights.end());
    std::uniform_real_distribution<qreal> nmrv(0.95,1.05);
    _atoms.resize(std::uniform_int_distribution<quint16>(50,500)(gen));
    qreal nmr = std::uniform_real_distribution<qreal>(0.5,4.0)(gen);
    for (int i = 1;i <= _atoms.size();i++)
    {
        _atoms[i-1] = new Atom(
            i
            ,qreal(i)*nmr*nmrv(gen)
            ,QColor(color(gen),color(gen),color(gen))
            ,static_cast<Atom::Bond>(bond(gen))
            ,static_cast<Atom::Bond>(bond(gen))
            ,static_cast<Atom::Bond>(bond(gen))
            ,static_cast<Atom::Bond>(bond(gen))
            ,this
            );
    }
    emit atomsReset();
}

Atoms::Atoms():
    GObject(QGuiApplication::instance())
{
    Q_ASSERT(parent());
}
