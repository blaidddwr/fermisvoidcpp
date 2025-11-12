#ifndef ATOM_H
#define ATOM_H
#include <QColor>

/*
 * Mass is measured in dalton (u).
 */
class Atom
{
public:
    enum class Bond {
        Positive
        ,Negative
        ,Covalent
    };
    enum class Direction {
        Top
        ,Right
        ,Bottom
        ,Left
    };
    static bool canBond(Bond b0,Bond b1);
    static Direction direction(int index);
    Atom(
        int atomicNumber
        ,qreal mass
        ,const QColor& color
        ,Bond topBond
        ,Bond rightBond
        ,Bond bottomBond
        ,Bond leftBond
        );
    Bond bond(Direction d) const;
    const QColor& color() const { return _color; }
    int atomicNumber() const { return _atomicNumber; }
    int charge() const;
    qreal mass() const { return _mass; }
private:
    Bond _bonds[4];
    QColor _color;
    int _atomicNumber;
    qreal _mass;
};

#endif
