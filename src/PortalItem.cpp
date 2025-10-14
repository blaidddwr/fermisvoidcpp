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

QuickRenderer* PortalItem::createRenderer()
{
    return new PortalRenderer;
}

void PortalItem::sync(QuickRenderer* renderer)
{
    auto pr = qobject_cast<PortalRenderer*>(renderer);
    Q_ASSERT(pr);
    _warp->sync(pr->warp());
    _atom->sync(pr->atom());
}

void PortalItem::timerEvent(QTimerEvent* event)
{
    if (window()) window()->update();
    event->accept();
}
