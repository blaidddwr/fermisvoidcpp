#ifndef ATOMLISTMODEL_H
#define ATOMLISTMODEL_H
#include "Atom.h"
#include <QAbstractListModel>

class AtomListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role
    {
        AtomicNumberRole = Qt::UserRole
        ,MassRole
        ,ColorRole
        ,BondsRole
    };
    AtomListModel();
    Q_INVOKABLE const Atom* getAtom(int atomicNumber) const;
    virtual QHash<int,QByteArray> roleNames() const override final;
    virtual QVariant data(const QModelIndex& index,int role=Qt::DisplayRole) const override final;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override final;
private slots:
    void onAtomsAboutToReset();
    void onAtomsReset();
};

#endif
