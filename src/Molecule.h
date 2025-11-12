#ifndef MOLECULE_H
#define MOLECULE_H
#include <QColor>
#include <QHash>
#include <QMap>
#include <QPoint>

/*
 * Hash is SHA256 (32 bytes).
 * Molar mass is measured in grams per mole (g/mol).
 * Stability must be greater than zero.
 * Charge must be zero.
 */
class Molecule
{
public:
    static constexpr qreal StabilityBase {1.0};
    static constexpr qreal StabilityMod {0.1};
    static constexpr qreal StabilityNP {0.01};
    static QPoint neighbor(const QPoint& position,int index);
    Molecule();
    Molecule(int atomicNumber);
    Molecule(const Molecule& other) = default;
    Molecule(Molecule&& other);
    Molecule& operator=(const Molecule& other) = default;
    Molecule& operator=(Molecule&& other);
    QList<QPoint> availablePositions() const;
    QList<QPoint> positions() const { return _atoms.keys(); }
    QList<int> availableAtoms(const QPoint& position) const;
    bool addAtom(const QPoint& position,int atomicNumber);
    bool canAddAtom(const QPoint& position,int atomicNumber) const;
    bool canRemoveAtom(const QPoint& position) const;
    bool isEmpty() const { return _atoms.isEmpty(); }
    bool removeAtom(const QPoint& position);
    const QByteArray& hash() const { return _hash; }
    const QColor& color() const { return _color; }
    const QHash<QPoint,int>& atoms() const { return _atoms; }
    const QMap<QPoint,int>& mappedAtoms() const { return _mappedAtoms; }
    int atom(const QPoint& position) const { return _atoms.value(position,-1); }
    int charge() const { return _charge; }
    int size() const { return _atoms.size(); }
    qreal molarMass() const { return _molarMass; }
    qreal radius() const { return _radius; }
    qreal stability() const { return _stability; }
private:
    void update();
    QByteArray _hash;
    QColor _color;
    QHash<QPoint,int> _atoms;
    QMap<QPoint,int> _mappedAtoms;
    int _charge {0};
    qreal _molarMass {0.0};
    qreal _radius {0.0};
    qreal _stability {0.0};
};

bool operator<(const QPoint& p0,const QPoint& p1);
bool operator==(const Molecule& m0, const Molecule& m1);
size_t qHash(const Molecule& key,size_t seed);

#endif
