#include "PortalRenderer.h"
#include "WarpRenderer.h"

PortalRenderer::PortalRenderer():
    _warp(new WarpRenderer(this))
{}

void PortalRenderer::setWarpColor(const QColor& value)
{
    _warp->setWarpColor(value);
}

void PortalRenderer::setEVColor(const QColor& value)
{
    _warp->setEVColor(value);
}

void PortalRenderer::setWarpRadius(qreal value)
{
    _warp->setRadius(value);
}

const QMatrix4x4& PortalRenderer::view() const
{
    return _view;
}

const QMatrix4x4& PortalRenderer::projection() const
{
    return _projection;
}

qreal PortalRenderer::scale() const
{
    return _scale;
}

void PortalRenderer::initGL()
{
    _warp->initGL();
}

void PortalRenderer::paintGL()
{
    if (_updateProjection)
    {
        _projection = QMatrix4x4();
        auto a = aspectRatio();
        _projection.ortho(-a,a,-1,1,-1,1);
        _warp->updateProjection();
        _updateProjection = false;
    }
    _warp->renderGL();
}

void PortalRenderer::resizeGL()
{
    _updateProjection = true;
}
