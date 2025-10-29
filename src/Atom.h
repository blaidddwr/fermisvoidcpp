#ifndef ATOM_H
#define ATOM_H
#include <QColor>

/*
 * Mass is measured in dalton (u).
 */
class Atom
{
public:
    enum Bond {
        Positive
        ,Negative
        ,Covalent
    };
    static bool canBond(Bond b0,Bond b1);
    Atom(
        int atomicNumber
        ,qreal mass
        ,const QColor& color
        ,Bond topBond
        ,Bond rightBond
        ,Bond bottomBond
        ,Bond leftBond
        );
    Bond bottomBond() const { return _bottomBond; }
    Bond leftBond() const { return _leftBond; }
    Bond rightBond() const { return _rightBond; }
    Bond topBond() const { return _topBond; }
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
