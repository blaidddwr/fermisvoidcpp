#ifndef PORTALITEM_H
#define PORTALITEM_H
#include "QuickItem.h"
class PortalRenderer;

class PortalItem : public QuickItem
{
    Q_OBJECT
public:
    PortalItem(QQuickItem* parent = nullptr);
signals:
    void rendererCreated(PortalRenderer* renderer);
    void syncRenderers(PortalRenderer* renderer);
protected:
    virtual QuickRenderer* createRenderer() override final;
    virtual void sync(QuickRenderer* renderer) override final;
    virtual void timerEvent(QTimerEvent* event) override final;
};

#endif
