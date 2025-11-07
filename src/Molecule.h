#ifndef MOLECULE_H
#define MOLECULE_H
#include <QHash>
#include <QPoint>
//TODO: add MoleculeModel to expose molecules to QML(like atoms)

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
    bool isEmpty() const { return _atoms.isEmpty(); }
    const QHash<QPoint,int>& atoms() const { return _atoms; }
    const QPointF& center() const { return _center; }
    int atom(const QPoint& position) const { return _atoms.value(position,-1); }
    int size() const { return _atoms.size(); }
    qreal freezingPoint() const { return _freezingPoint; }
    qreal molarMass() const { return _molarMass; }
    qreal radius() const { return _radius; }
private:
    void update();
    QHash<QPoint,int> _atoms;
    QPointF _center {0.0,0.0};
    qreal _freezingPoint {0.0};
    qreal _molarMass {0.0};
    qreal _radius {0.0};
};

#endif
