#ifndef ATOM_H
#define ATOM_H
#include "GObject.h"
#include <QColor>

/*
 * Mass is measured in Dalton(u).
 * Bonds are true for positive and false for negative.
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
    Q_PROPERTY(int atomicNumber READ atomicNumber CONSTANT)
    Q_PROPERTY(qreal mass READ mass CONSTANT)
    Q_PROPERTY(QColor color READ color CONSTANT)
    Q_PROPERTY(Bond topBond READ topBond CONSTANT)
    Q_PROPERTY(Bond rightBond READ rightBond CONSTANT)
    Q_PROPERTY(Bond bottomBond READ bottomBond CONSTANT)
    Q_PROPERTY(Bond leftBond READ leftBond CONSTANT)
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
    int atomicNumber() const { return _atomicNumber; }
    qreal mass() const { return _mass; }
    const QColor& color() const { return _color; }
    Bond topBond() const { return _topBond; }
    Bond rightBond() const { return _rightBond; }
    Bond bottomBond() const { return _bottomBond; }
    Bond leftBond() const { return _leftBond; }
private:
    int _atomicNumber;
    qreal _mass;
    QColor _color;
    Bond _topBond;
    Bond _rightBond;
    Bond _bottomBond;
    Bond _leftBond;
};

#endif
