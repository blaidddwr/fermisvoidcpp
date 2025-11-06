#include "GameRenderer.h"
#include "PortalRenderer.h"

GameRenderer::GameRenderer(PortalRenderer* parent):
    QObject(parent)
{
    Q_ASSERT(parent);
    connect(parent,&PortalRenderer::initRenderers,this,&GameRenderer::initGL,Qt::DirectConnection);
    connect(
        parent
        ,&PortalRenderer::projectionChanged
        ,this
        ,&GameRenderer::onProjectionChanged
        ,Qt::DirectConnection
        );
}

const QMatrix4x4& GameRenderer::projection()
{
    _projectionUpdated = false;
    return PortalRenderer::instance()->projection();
}

const QMatrix4x4& GameRenderer::view()
{
    _viewUpdated = false;
    return _view;
}

void GameRenderer::release()
{
    Q_ASSERT(_retained > 0);
    if (!--_retained) PortalRenderer::instance()->remove(this);
}

void GameRenderer::setView(const QMatrix4x4& value)
{
    if (_view != value)
    {
        _view = value;
        _viewUpdated = true;
    }
}

void GameRenderer::use()
{
    if (!_retained++) PortalRenderer::instance()->add(this);
}

void GameRenderer::onProjectionChanged()
{
    _projectionUpdated = true;
}
