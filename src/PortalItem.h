#ifndef PORTALITEM_H
#define PORTALITEM_H
#include "AtomItem.h"
#include "Latch.h"
#include "QuickItem.h"
#include "WarpItem.h"
class OpenGLItem;

class PortalItem : public QuickItem
{
    Q_OBJECT
public:
    Q_PROPERTY(AtomItem* atom READ atom CONSTANT)
    Q_PROPERTY(WarpItem* warp READ warp CONSTANT)
    static PortalItem& instance();
    PortalItem(QQuickItem* parent = nullptr);
    AtomItem* atom() const { return _atom; }
    Q_INVOKABLE void clearActive();
    WarpItem* warp() const { return _warp; }
    void activate(OpenGLItem* item);
protected:
    virtual QuickRenderer* createRenderer() override final;
    virtual void sync(QuickRenderer* renderer) override final;
    virtual void timerEvent(QTimerEvent* event) override final;
private:
    static PortalItem* _instance;
    AtomItem* _atom {nullptr};
    Latch<OpenGLItem*> _active {nullptr};
    WarpItem* _warp {nullptr};
};

#endif
