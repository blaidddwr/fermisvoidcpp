#ifndef MOLECULE_H
#define MOLECULE_H
#include <QHash>
#include <QPoint>
//TODO: add MoleculeModel to expose molecules to QML(like atoms)
//TODO: make AtomListModel(which will be property of MoleculeModel) that lists the atoms of a molecule

/*
 * Molar mass is measured in grams (g).
 * Freezing point is measured in kelvin (K).
 * Liquid slope is measured in kelvin over pascals (K/Pa).
 */
class Molecule
{
public:
    static constexpr qreal FreezingPointA {11.33};
    static constexpr qreal FreezingPointB {2.1259};
    static Molecule generate();
    Molecule() = default;
    Molecule(int atomicNumber);
    Molecule(const Molecule& other) = default;
    Molecule(Molecule&& other);
    Molecule& operator=(const Molecule& other) = default;
    Molecule& operator=(Molecule&& other);
    QHash<int,int> atoms() const;
    QList<QPoint> availablePositions() const;
    QList<QPoint> positions() const { return _atoms.keys(); }
    QList<int> availableAtoms(const QPoint& position) const;
    bool addAtom(const QPoint& position,int atomicNumber);
    bool isEmpty() const { return _atoms.isEmpty(); }
    int atom(const QPoint& position) const { return _atoms.value(position,-1); }
    qreal freezingPoint() const { return _freezingPoint; }
    qreal liquidSlope() const { return _liquidSlope; }
    qreal molarMass() const { return _molarMass; }
private:
    void update();
    QHash<QPoint,int> _atoms;
    qreal _freezingPoint {0.0};
    qreal _liquidSlope {0.0};
    qreal _molarMass {0.0};
};

#endif
