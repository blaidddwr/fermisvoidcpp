#include "Atom.h"
#include "AtomModel.h"
#include "Atoms.h"

AtomModel::AtomModel(QObject *parent):
    QObject(parent)
{}

const QColor& AtomModel::color() const
{
    static const QColor def;
    return _atom ? _atom->color() : def;
}

int AtomModel::atomicNumber() const
{
    return _atom ? _atom->atomicNumber() : -1;
}

int AtomModel::charge() const
{
    return _atom ? _atom->charge() : 0;
}

qreal AtomModel::mass() const
{
    return _atom ? _atom->mass() : 0.0;
}

void AtomModel::setAtomicNumber(int value)
{
    Q_ASSERT(
        value == -1
        || (
            value > 0
            && value <= Atoms::instance().size()
            )
        );
    int can = _atom ? _atom->atomicNumber() : -1;
    if (can != value)
    {
        if (value == -1) _atom = nullptr;
        else { _atom = &Atoms::instance().get(value); }
        emit colorChanged(color());
        emit chargeChanged(charge());
        emit massChanged(mass());
        emit atomicNumberChanged(value);
    }
}
