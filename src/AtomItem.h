#ifndef ATOMITEM_H
#define ATOMITEM_H
#include "AtomInstance.h"
#include "Latch.h"
#include <QObject>
class AtomRenderer;

class AtomItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal radius READ radius NOTIFY radiusChanged);
public:
    explicit AtomItem(QObject *parent = nullptr);
    qreal radius() const { return _radius; }
    void sync(AtomRenderer& renderer);
signals:
    void radiusChanged(qreal value);
public slots:
    void setAtom(int atomicNumber);
private:
    void setRadius(qreal value);
    Latch<QList<AtomInstance>> _atoms;
    qreal _radius {0.0};
};

#endif
