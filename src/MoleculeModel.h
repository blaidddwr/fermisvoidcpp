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
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)
    Q_PROPERTY(int charge READ charge NOTIFY chargeChanged)
    Q_PROPERTY(qreal molarMass READ molarMass NOTIFY molarMassChanged)
    Q_PROPERTY(qreal radius READ radius NOTIFY radiusChanged)
    Q_PROPERTY(qreal stability READ stability NOTIFY stabilityChanged)
    Q_INVOKABLE QList<int> availableAtoms(const QPoint& position) const;
    Q_INVOKABLE bool addAtom(const QPoint& position,int atomicNumber);
    Q_INVOKABLE bool removeAtom(const QPoint& position);
    const Molecule& molecule() const { return _molecule; }
    const QColor& color() const { return _molecule.color(); }
    int charge() const { return _molecule.charge(); }
    qreal molarMass() const { return _molecule.molarMass(); }
    qreal radius() const { return _molecule.radius(); }
    qreal stability() const { return _molecule.stability(); }
    virtual QHash<int,QByteArray> roleNames() const override final;
    virtual QVariant data(const QModelIndex& index,int role=Qt::DisplayRole) const override final;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override final;
signals:
    void chargeChanged(int value);
    void colorChanged(const QColor& value);
    void freezingPointChanged(qreal value);
    void heatConductivityChanged(qreal value);
    void molarHeatCapacityChanged(qreal value);
    void molarMassChanged(qreal value);
    void moleculeChanged(const Molecule& value);
    void radiusChanged(qreal value);
    void stabilityChanged(qreal value);
private:
    void addLocation(const QPoint& position);
    void removeLocation(const QList<QPoint>& availablePositions,const QPoint& position);
    Molecule _molecule;
    QList<QPoint> _locations {{0,0}};
};

#endif
