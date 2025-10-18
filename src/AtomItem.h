#ifndef ATOMITEM_H
#define ATOMITEM_H
#include "AtomInstance.h"
#include "Latch.h"
#include "OpenGLItem.h"
class AtomRenderer;

class AtomItem : public OpenGLItem
{
    Q_OBJECT
    Q_PROPERTY(qreal radius READ radius NOTIFY radiusChanged);
public:
    explicit AtomItem(PortalItem *parent = nullptr);
    Q_INVOKABLE void setAtom(int atomicNumber);
    qreal radius() const { return _radius; }
signals:
    void radiusChanged(qreal value);
protected:
    virtual OpenGLRenderer* _createRenderer() const override final;
    virtual void _sync(OpenGLRenderer* renderer) override final;
private:
    Latch<QList<AtomInstance>> _atoms;
    qreal _radius {0.0};
    void setRadius(qreal value);
};

#endif
