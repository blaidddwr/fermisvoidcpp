#ifndef ATOMLISTMODEL_H
#define ATOMLISTMODEL_H
#include <QAbstractListModel>

class AtomListModel : public QAbstractListModel
{
    enum Role
    {
        AtomicNumberRole = Qt::UserRole
        ,MassRole
        ,ColorRole
        ,ChargeRole
    };
public:
    AtomListModel();
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override final;
    virtual QVariant data(const QModelIndex& index,int role=Qt::DisplayRole) const override final;
    virtual QHash<int,QByteArray> roleNames() const override final;
private slots:
    void onAtomsAboutToReset();
    void onAtomsReset();
};

#endif
