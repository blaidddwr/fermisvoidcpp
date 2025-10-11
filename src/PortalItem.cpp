#include "PortalItem.h"
#include "PortalRenderer.h"
#include <QQuickWindow>

PortalItem::PortalItem(QQuickItem* parent):
    QuickItem(parent)
{
    startTimer(16);
}

const QColor& PortalItem::warpColor() const
{
    return _warpColor.peek();
}

const QColor& PortalItem::evColor() const
{
    return _evColor.peek();
}

qreal PortalItem::warpRadius() const
{
    return _warpRadius.peek();
}

void PortalItem::setWarpColor(const QColor& value)
{
    if (_warpColor.peek() != value)
    {
        _warpColor.set(value);
        emit warpColorChanged(value);
    }
}

void PortalItem::setEVColor(const QColor& value)
{
    if (_evColor.peek() != value)
    {
        _evColor.set(value);
        emit evColorChanged(value);
    }
}

void PortalItem::setWarpRadius(qreal value)
{
    if (_warpRadius.peek() != value)
    {
        _warpRadius.set(value);
        emit warpRadiusChanged(value);
    }
}

QuickRenderer* PortalItem::createRenderer()
{
    return new PortalRenderer;
}

void PortalItem::sync(QuickRenderer* renderer)
{
    auto pr = qobject_cast<PortalRenderer*>(renderer);
    Q_ASSERT(pr);
    if (_warpColor.updated()) pr->setWarpColor(_warpColor.get());
    if (_evColor.updated()) pr->setEVColor(_evColor.get());
    if (_warpRadius.updated()) pr->setWarpRadius(_warpRadius.get());
}

void PortalItem::timerEvent(QTimerEvent* event)
{
    if (window()) window()->update();
    event->accept();
}
