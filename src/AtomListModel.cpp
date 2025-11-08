#include "Atom.h"
#include "AtomListModel.h"
#include "Atoms.h"
#include <QHash>

AtomListModel::AtomListModel(QObject* parent):
    QAbstractListModel(parent)
{
    for (int a = 1;a <= Atoms::instance().size();a++) _atoms.append(a);
}

AtomListModel::AtomListModel(const QList<int>& atoms,QObject* parent):
    QAbstractListModel(parent)
    ,_atoms(atoms)
{}

int AtomListModel::atomicNumber(int row) const
{
    Q_ASSERT(row >= 0);
    Q_ASSERT(row < _atoms.size());
    return _atoms.at(row);
}

int AtomListModel::indexOf(int atomicNumber) const
{
    return _atoms.indexOf(atomicNumber);
}

QHash<int,QByteArray> AtomListModel::roleNames() const
{
    return {
        {AtomicNumberRole,"atomicNumber"}
        ,{MassRole,"mass"}
        ,{ColorRole,"atomicColor"}
        ,{BondsRole,"bonds"}
    };
}

QVariant AtomListModel::data(const QModelIndex& index,int role) const
{
    Q_ASSERT(index.isValid());
    Q_ASSERT(index.row() >= 0);
    Q_ASSERT(index.column() == 0);
    if (index.row() >= _atoms.size()) return QVariant();
    auto an = _atoms.at(index.row());
    switch (role)
    {
    case AtomicNumberRole:
        return Atoms::instance().get(an).atomicNumber();
    case MassRole:
        return Atoms::instance().get(an).mass();
    case ColorRole:
        return Atoms::instance().get(an).color();
    case BondsRole:
    {
        const auto& atom = Atoms::instance().get(an);
        QString ret;
        for (auto bond: {atom.topBond(),atom.rightBond(),atom.bottomBond(),atom.leftBond()})
        {
            switch (bond)
            {
            case Atom::Bond::Positive:
                ret += "+";
                break;
            case Atom::Bond::Negative:
                ret += "-";
                break;
            case Atom::Bond::Covalent:
                ret += "=";
                break;
            }
        }
        return ret;
    }
    default:
        return QVariant();
    }
}

int AtomListModel::rowCount(const QModelIndex& parent) const
{
    Q_ASSERT(!parent.isValid());
    return _atoms.size();
}

void AtomListModel::setAtoms(const QList<int>& atoms)
{
    if (_atoms != atoms)
    {
        beginResetModel();
        _atoms = atoms;
        endResetModel();
        emit atomsChanged(atoms);
    }
}
