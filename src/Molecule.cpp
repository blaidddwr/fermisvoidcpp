#include "Atom.h"
#include "Atoms.h"
#include "Molecule.h"
#include <QCryptographicHash>
#include <QSet>

QPoint Molecule::neighbor(const QPoint& position,int index)
{
    switch(Atom::direction(index))
    {
    case Atom::Direction::Top:
        return {position.x(),position.y()+1};
    case Atom::Direction::Right:
        return {position.x()+1,position.y()};
    case Atom::Direction::Bottom:
        return {position.x(),position.y()-1};
    case Atom::Direction::Left:
        return {position.x()-1,position.y()};
    default:
        return position;
    }
}

Molecule::Molecule():
    _hash(QCryptographicHash(QCryptographicHash::Sha256).result())
{}

Molecule::Molecule(int atomicNumber):
    _hash(QCryptographicHash(QCryptographicHash::Sha256).result())
{
    Q_ASSERT(atomicNumber > 0);
    Q_ASSERT(atomicNumber <= Atoms::instance().size());
    addAtom({0,0},atomicNumber);
}

Molecule::Molecule(Molecule&& other):
    _hash(other._hash)
    ,_color(other._color)
    ,_atoms(std::move(other._atoms))
    ,_mappedAtoms(std::move(other._mappedAtoms))
    ,_charge(other._charge)
    ,_molarMass(other._molarMass)
    ,_stability(other._stability)
{
    other._hash = QCryptographicHash(QCryptographicHash::Sha256).result();
    other._color = QColor();
    other._charge = 0;
    other._molarMass = 0.0;
    other._stability = 0.0;
}

Molecule& Molecule::operator=(Molecule&& other)
{
    _hash = other._hash;
    _color = other._color;
    _atoms = std::move(other._atoms);
    _mappedAtoms = std::move(other._mappedAtoms);
    _charge = other._charge;
    _molarMass = other._molarMass;
    _stability = other._stability;
    other._hash = QCryptographicHash(QCryptographicHash::Sha256).result();
    other._color = QColor();
    other._charge = 0;
    other._molarMass = 0.0;
    other._stability = 0.0;
    return *this;
}

QList<int> Molecule::availableAtoms(const QPoint& position) const
{
    QList<int> ret;
    auto& atoms = Atoms::instance();
    for (int a = 1;a <= atoms.size();a++)
    {
        if (canAddAtom(position,a)) ret.append(a);
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
        for (int i = 0;i < 4;i++)
        {
            auto np = neighbor(pos,i);
            if (!ps.contains(np)) ret.insert(np);
        }
    }
    return ret.values();
}

bool Molecule::addAtom(const QPoint& position,int atomicNumber)
{
    if (!canAddAtom(position,atomicNumber)) return false;
    _atoms[position] = atomicNumber;
    _mappedAtoms[position] = atomicNumber;
    update();
    return true;
}

bool Molecule::canAddAtom(const QPoint& position,int atomicNumber) const
{
    auto& atoms = Atoms::instance();
    for (int i = 0;i < 4;i++)
    {
        if (!atoms.canBond(atomicNumber,atom(neighbor(position,i)),Atom::direction(i)))
        {
            return false;
        }
    }
    return true;
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
            for (int i = 0;i < 4;i++) travel(neighbor(pos,i));
        }
    };
    for (int i = 0;i < 4;i++)
    {
        auto pos = neighbor(position,i);
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
    _atoms.erase(i);
    auto mi = _mappedAtoms.find(position);
    Q_ASSERT(mi != _mappedAtoms.end());
    _mappedAtoms.erase(mi);
    update();
    return true;
}

void Molecule::update()
{
    QByteArray sd;
    QDataStream sdin(&sd,QIODeviceBase::WriteOnly);
    int r = 0;
    int g = 0;
    int b = 0;
    _radius = 0.0;
    _charge = 0;
    _molarMass = 0.0;
    _stability = _atoms.isEmpty() ? 0.0 : StabilityBase;
    for (auto i = _mappedAtoms.cbegin();i != _mappedAtoms.cend();i++)
    {
        const auto& pos = i.key();
        const auto& atom = Atoms::instance().get(i.value());
        r += atom.color().red();
        g += atom.color().green();
        b += atom.color().blue();
        sdin << pos.x() << pos.y() << atom.atomicNumber();
        auto rs = qreal(pos.x()*pos.x())+(pos.y()*pos.y());
        _stability -= StabilityNP*rs;
        for (int i = 0;i < 4;i++)
        {
            if (_atoms.contains(neighbor(pos,i)))
            {
                if (atom.bond(Atom::direction(i)) == Atom::Bond::Covalent)
                {
                    _stability += StabilityMod;
                }
                else _stability -= StabilityMod;
            }
        }
        _radius = qMax(_radius,rs);
        _charge += atom.charge();
        _molarMass += atom.mass();
    }
    _color.setRgb(r/_atoms.size(),g/_atoms.size(),b/_atoms.size());
    _radius = sqrt(_radius);
    QCryptographicHash sha256(QCryptographicHash::Sha256);
    sha256.addData(sd);
    _hash = sha256.result();
}

bool operator<(const QPoint& p0,const QPoint& p1)
{
    if (p0.x() == p1.x()) return p0.y() < p1.y();
    else return p0.x() < p1.x();
}

bool operator==(const Molecule& m0, const Molecule& m1)
{
    return m0.atoms() == m1.atoms();
}

size_t qHash(const Molecule& key,size_t seed)
{
    return qHash(key.hash(),seed);
}
