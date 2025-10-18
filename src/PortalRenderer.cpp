#include "PortalRenderer.h"
#include "SinesRenderer.h"
#include "WarpRenderer.h"

PortalRenderer::PortalRenderer(const QList<OpenGLRenderer*>& renderers):
    _renderers(renderers)
    ,_sines(new SinesRenderer(this))
    ,_warp(new WarpRenderer(this))
{
    for (auto r: std::as_const(_renderers)) r->setParent(this);
}

void PortalRenderer::setActive(OpenGLRenderer* renderer)
{
    Q_ASSERT(
        !renderer
        || renderer->parent() == this
        );
    _active = renderer;
}

void PortalRenderer::initGL()
{
    _sines->initGL();
    _warp->initGL();
    for (auto r: std::as_const(_renderers)) r->initGL();
}

void PortalRenderer::paintGL()
{
    auto active = _active.peek();
    if (
        _active.updated()
        && active
        )
    {
        _active.get();
        active->updateProjection();
    }
    if (_updateProjection)
    {
        _projection = QMatrix4x4();
        auto a = aspectRatio();
        _projection.ortho(-a,a,-1.0,1.0,-1.0,1.0);
        _warp->updateProjection();
        if (active) active->updateProjection();
        _updateProjection = false;
    }
    _sines->renderGL();
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    _warp->renderGL();
    if (active) active->renderGL();
    glClear(GL_DEPTH_BUFFER_BIT);
}

void PortalRenderer::resizeGL()
{
    _updateProjection = true;
}
