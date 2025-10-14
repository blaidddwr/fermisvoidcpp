#ifndef PORTALITEM_H
#define PORTALITEM_H
#include "AtomItem.h"
#include "QuickItem.h"
#include "WarpItem.h"

class PortalItem : public QuickItem
{
    Q_OBJECT
public:
    Q_PROPERTY(AtomItem* atom READ atom CONSTANT)
    Q_PROPERTY(WarpItem* warp READ warp CONSTANT)
    static PortalItem& instance();
    PortalItem(QQuickItem* parent = nullptr);
    AtomItem* atom() const { return _atom; }
    WarpItem* warp() const { return _warp; }
protected:
    virtual QuickRenderer* createRenderer() override final;
    virtual void sync(QuickRenderer* renderer) override final;
    virtual void timerEvent(QTimerEvent* event) override final;
private:
    static PortalItem* _instance;
    AtomItem* _atom {nullptr};
    WarpItem* _warp {nullptr};
};

#endif
