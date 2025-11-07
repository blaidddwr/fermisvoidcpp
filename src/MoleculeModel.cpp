#include "MoleculeModel.h"

MoleculeModel::MoleculeModel(QObject *parent):
    QAbstractListModel(parent)
{}

bool MoleculeModel::addAtom(const QPoint& position,int atomicNumber)
{
    if (_molecule.addAtom(position,atomicNumber))
    {
        int row = _locations.indexOf(position);
        Q_ASSERT(row >= 0);
        addLocation({position.x(),position.y()+1});
        addLocation({position.x()+1,position.y()});
        addLocation({position.x(),position.y()-1});
        addLocation({position.x()-1,position.y()});
        auto i = index(row);
        emit dataChanged(i,i,{AtomicNumberRole});
        emit centerChanged(_molecule.center());
        emit freezingPointChanged(_molecule.freezingPoint());
        emit molarMassChanged(_molecule.molarMass());
        emit radiusChanged(_molecule.radius());
        return true;
    }
    else return false;
}

QHash<int,QByteArray> MoleculeModel::roleNames() const
{
    return {
        {XRole,"x"}
        ,{YRole,"y"}
        ,{AtomicNumberRole,"atomicNumber"}
    };
}

QVariant MoleculeModel::data(const QModelIndex& index,int role) const
{
    Q_ASSERT(index.isValid());
    Q_ASSERT(index.row() >= 0);
    Q_ASSERT(index.column() == 0);
    if (index.row() >= _locations.size()) return QVariant();
    const auto p = _locations.at(index.row());
    switch (role)
    {
    case AtomicNumberRole:
        return _molecule.atom(p);
    case XRole:
        return p.x();
    case YRole:
        return p.y();
    default:
        return QVariant();
    }
}

int MoleculeModel::rowCount(const QModelIndex& parent) const
{
    Q_ASSERT(!parent.isValid());
    return _locations.size();
}

void MoleculeModel::addLocation(const QPoint& position)
{
    if (_locations.indexOf(position) == -1)
    {
        auto ni = _locations.size();
        beginInsertRows(QModelIndex(),ni,ni);
        _locations.append(position);
        endInsertRows();
    }
}
