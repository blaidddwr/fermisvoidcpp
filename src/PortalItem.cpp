#include "PortalItem.h"
#include "PortalRenderer.h"
#include <QQuickWindow>

PortalItem* PortalItem::_instance {nullptr};

PortalItem& PortalItem::instance()
{
    Q_ASSERT(_instance);
    return *_instance;
}

PortalItem::PortalItem(QQuickItem* parent):
    QuickItem(parent)
    ,_atom(new AtomItem(this))
    ,_warp(new WarpItem(this))
{
    Q_ASSERT(!_instance);
    _instance = this;
    startTimer(16);
}

void PortalItem::clearActive()
{
    _active.set() = nullptr;
}

void PortalItem::activate(OpenGLItem* item)
{
    _active.set() = item;
}

QuickRenderer* PortalItem::createRenderer()
{
    return new PortalRenderer({_atom->createRenderer()});
}

void PortalItem::sync(QuickRenderer* renderer)
{
    static const QPointF defaultOffset {0.0,0.0};
    auto active = _active.peek();
    auto pr = qobject_cast<PortalRenderer*>(renderer);
    Q_ASSERT(pr);
    pr->setScale(active ? active->scale() : 1.0);
    pr->setOffset(active ? active->offset() : defaultOffset);
    _warp->setActualRadius(active ? active->radius() : 0.0);
    _warp->sync(pr->warp());
    if (_active.updated())
    {
        _active.get();
        pr->setActive(active ? active->renderer() : nullptr);
    }
    if (active) active->sync();
}

void PortalItem::timerEvent(QTimerEvent* event)
{
    if (window()) window()->update();
    event->accept();
}
