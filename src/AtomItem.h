#ifndef ATOMITEM_H
#define ATOMITEM_H
#include "AtomInstance.h"
#include "Latch.h"
#include <QObject>
class AtomRenderer;

class AtomItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal desiredWarpRadius READ desiredWarpRadius NOTIFY desiredWarpRadiusChanged);
public:
    explicit AtomItem(QObject *parent = nullptr);
    void sync(AtomRenderer& renderer);
    qreal desiredWarpRadius() const { return _desiredWarpRadius; }
signals:
    void desiredWarpRadiusChanged(qreal value);
public slots:
    void setAtom(int atomicNumber);
private:
    void setDesiredWarpRadius(qreal value);
    Latch<QList<AtomInstance>> _atoms;
    qreal _desiredWarpRadius {0.0};
};

#endif
