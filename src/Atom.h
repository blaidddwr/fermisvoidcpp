#ifndef ATOM_H
#define ATOM_H
#include "GObject.h"
#include <QColor>
//TODO: change this to value object(NOT qobject) because it is not unique
//TODO: make AtomModel to expose an atom to QML (setAtomicNumber(int) to change it)

/*
 * Mass is measured in dalton (u).
 */
class Atom : public GObject
{
    Q_OBJECT
public:
    enum Bond {
        Positive
        ,Negative
        ,Covalent
    };
    Q_ENUM(Bond)
    Q_PROPERTY(Bond bottomBond READ bottomBond CONSTANT)
    Q_PROPERTY(Bond leftBond READ leftBond CONSTANT)
    Q_PROPERTY(Bond rightBond READ rightBond CONSTANT)
    Q_PROPERTY(Bond topBond READ topBond CONSTANT)
    Q_PROPERTY(QColor color READ color CONSTANT)
    Q_PROPERTY(bool life READ life CONSTANT)
    Q_PROPERTY(bool solvent READ solvent CONSTANT)
    Q_PROPERTY(int atomicNumber READ atomicNumber CONSTANT)
    Q_PROPERTY(int charge READ charge CONSTANT)
    Q_PROPERTY(qreal mass READ mass CONSTANT)
    static bool canBond(Bond b0,Bond b1);
    Atom(
        int atomicNumber
        ,qreal mass
        ,const QColor& color
        ,Bond topBond
        ,Bond rightBond
        ,Bond bottomBond
        ,Bond leftBond
        ,QObject *parent = nullptr
        );
    Bond bottomBond() const { return _bottomBond; }
    Bond leftBond() const { return _leftBond; }
    Bond rightBond() const { return _rightBond; }
    Bond topBond() const { return _topBond; }
    bool life() const;
    bool solvent() const;
    const QColor& color() const { return _color; }
    int atomicNumber() const { return _atomicNumber; }
    int charge() const;
    qreal mass() const { return _mass; }
private:
    Bond _topBond;
    Bond _rightBond;
    Bond _bottomBond;
    Bond _leftBond;
    QColor _color;
    int _atomicNumber;
    qreal _mass;
};

#endif
