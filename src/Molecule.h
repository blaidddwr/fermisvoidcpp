#ifndef MOLECULE_H
#define MOLECULE_H
#include <QHash>
#include <QPoint>

/*
 * Molar mass is measured in grams per mole (g/mol).
 * Freezing point is measured in kelvin (K).
 * Liquid slope is measured in kelvin over pascals (K/Pa).
 */
class Molecule
{
public:
    static constexpr qreal FreezingPointA {11.33};
    static constexpr qreal FreezingPointB {2.1259};
    Molecule() = default;
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
    const QHash<QPoint,int>& atoms() const { return _atoms; }
    int atom(const QPoint& position) const { return _atoms.value(position,-1); }
    int size() const { return _atoms.size(); }
    qreal freezingPoint() const { return _freezingPoint; }
    qreal molarMass() const { return _molarMass; }
    qreal radius() const { return _radius; }
private:
    void update();
    QHash<QPoint,int> _atoms;
    qreal _freezingPoint {0.0};
    qreal _molarMass {0.0};
    qreal _radius {0.0};
};

#endif
