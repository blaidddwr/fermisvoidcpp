#ifndef MOLECULEMODEL_H
#define MOLECULEMODEL_H
#include "Molecule.h"
#include <QAbstractListModel>

class MoleculeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role
    {
        XRole = Qt::UserRole
        ,YRole
        ,AtomicNumberRole
    };
    Q_PROPERTY(QPointF center READ center NOTIFY centerChanged)
    Q_PROPERTY(qreal freezingPoint READ freezingPoint NOTIFY freezingPointChanged)
    Q_PROPERTY(qreal molarMass READ molarMass NOTIFY molarMassChanged)
    explicit MoleculeModel(QObject *parent = nullptr);
    Q_INVOKABLE QList<int> availableAtoms(const QPoint& position) const;
    Q_INVOKABLE bool addAtom(const QPoint& position,int atomicNumber);
    Q_INVOKABLE bool removeAtom(const QPoint& position);
    const Molecule& molecule() const { return _molecule; }
    const QPointF& center() const { return _molecule.center(); }
    qreal freezingPoint() const { return _molecule.freezingPoint(); }
    qreal molarMass() const { return _molecule.molarMass(); }
    virtual QHash<int,QByteArray> roleNames() const override final;
    virtual QVariant data(const QModelIndex& index,int role=Qt::DisplayRole) const override final;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override final;
signals:
    void centerChanged(const QPointF& value);
    void freezingPointChanged(qreal value);
    void molarMassChanged(qreal value);
private:
    void addLocation(const QPoint& position);
    void removeLocation(const QList<QPoint>& availablePositions,const QPoint& position);
    Molecule _molecule;
    QList<QPoint> _locations {{0,0}};
};

#endif
