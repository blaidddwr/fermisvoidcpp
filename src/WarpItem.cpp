#include "WarpItem.h"
#include "WarpRenderer.h"

WarpItem::WarpItem(QObject *parent)
    : QObject{parent}
{}

void WarpItem::setActualRadius(qreal value)
{
    if (_actualRadius.peek() != value)
    {
        _actualRadius = value;
        emit actualRadiusChanged(value);
    }
}

void WarpItem::setColor(const QColor& value)
{
    if (_color.peek() != value)
    {
        _color = value;
        emit colorChanged(value);
    }
}

void WarpItem::setEVColor(const QColor& value)
{
    if (_evColor.peek() != value)
    {
        _evColor = value;
        emit evColorChanged(value);
    }
}

void WarpItem::setRadius(qreal value)
{
    if (_radius.peek() != value)
    {
        _radius = value;
        emit radiusChanged(value);
    }
}

void WarpItem::sync(WarpRenderer& renderer)
{
    if (_color.updated()) renderer.setColor(_color.get());
    if (_evColor.updated()) renderer.setEVColor(_evColor.get());
    if (
        _radius.updated()
        || _actualRadius.updated()
        )
    {
        renderer.setRadius(_radius.get()*_actualRadius.get());
    }
}
