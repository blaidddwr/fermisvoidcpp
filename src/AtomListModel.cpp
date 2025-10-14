#include "Atom.h"
#include "AtomListModel.h"
#include "Atoms.h"
#include <QHash>

AtomListModel::AtomListModel()
{
    connect(&Atoms::instance()
        ,&Atoms::atomsAboutToReset
        ,this
        ,&AtomListModel::onAtomsAboutToReset
        );
    connect(&Atoms::instance(),&Atoms::atomsReset,this,&AtomListModel::onAtomsReset);
}

int AtomListModel::rowCount(const QModelIndex& parent) const
{
    Q_ASSERT(!parent.isValid());
    return Atoms::instance().size();
}

QVariant AtomListModel::data(const QModelIndex& index,int role) const
{
    Q_ASSERT(index.isValid());
    Q_ASSERT(index.row() >= 0);
    Q_ASSERT(index.column() == 0);
    if (index.row() >= Atoms::instance().size()) return QVariant();
    switch (role)
    {
    case AtomicNumberRole:
        return Atoms::instance().get(index.row()+1).atomicNumber();
    case MassRole:
        return Atoms::instance().get(index.row()+1).mass();
    case ColorRole:
        return Atoms::instance().get(index.row()+1).color();
    case ChargeRole:
    {
        const auto& atom = Atoms::instance().get(index.row()+1);
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

QHash<int,QByteArray> AtomListModel::roleNames() const
{
    return {
        {AtomicNumberRole,"atomicNumber"}
        ,{MassRole,"mass"}
        ,{ColorRole,"atomicColor"}
        ,{ChargeRole,"charge"}
    };
}

void AtomListModel::onAtomsAboutToReset()
{
    beginResetModel();
}

void AtomListModel::onAtomsReset()
{
    endResetModel();
}
