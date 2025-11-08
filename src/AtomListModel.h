#ifndef ATOMLISTMODEL_H
#define ATOMLISTMODEL_H
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
    Q_PROPERTY(QList<int> atoms READ atoms WRITE setAtoms NOTIFY atomsChanged)
    AtomListModel(QObject* parent = nullptr);
    AtomListModel(const QList<int>& atoms,QObject* parent = nullptr);
    Q_INVOKABLE int atomicNumber(int row) const;
    Q_INVOKABLE int indexOf(int atomicNumber) const;
    const QList<int>& atoms() const { return _atoms; }
    virtual QHash<int,QByteArray> roleNames() const override final;
    virtual QVariant data(const QModelIndex& index,int role=Qt::DisplayRole) const override final;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override final;
    void setAtoms(const QList<int>& atoms);
signals:
    void atomsChanged(const QList<int>& atoms);
private:
    QList<int> _atoms;
};

#endif
