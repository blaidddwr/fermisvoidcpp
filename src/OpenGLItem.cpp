#include "OpenGLItem.h"
#include "PortalItem.h"

OpenGLItem::OpenGLItem(PortalItem *parent):
    QObject(parent)
    ,_parent(parent)
{}

OpenGLRenderer* OpenGLItem::createRenderer()
{
    _renderer = _createRenderer();
    return _renderer;
}

void OpenGLItem::activate()
{
    Q_ASSERT(_parent);
    _parent->activate(this);
}

void OpenGLItem::sync()
{
    Q_ASSERT(_renderer);
    _sync(_renderer);
}

void OpenGLItem::setRadius(qreal value)
{
    if (_radius != value)
    {
        _radius = value;
        emit radiusChanged(value);
    }
}
