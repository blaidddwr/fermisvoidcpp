#include "Atom.h"
#include <QGuiApplication>

Atom::Atom(
    int atomicNumber
    ,qreal mass
    ,const QColor& color
    ,Bond topBond
    ,Bond rightBond
    ,Bond bottomBond
    ,Bond leftBond
    ,QObject* parent
    ):
    GObject(parent)
    ,_atomicNumber(atomicNumber)
    ,_mass(mass)
    ,_color(color)
    ,_topBond(topBond)
    ,_rightBond(rightBond)
    ,_bottomBond(bottomBond)
    ,_leftBond(leftBond)
{
    Q_ASSERT(atomicNumber >= 1);
}
