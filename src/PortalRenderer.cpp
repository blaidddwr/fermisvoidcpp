#include "AtomRenderer.h"
#include "PortalRenderer.h"
#include "WarpRenderer.h"

PortalRenderer::PortalRenderer():
    _atom(new AtomRenderer(this))
    ,_warp(new WarpRenderer(this))
{}

void PortalRenderer::initGL()
{
    _warp->initGL();
    _atom->initGL();
}

void PortalRenderer::paintGL()
{
    if (_updateProjection)
    {
        _projection = QMatrix4x4();
        auto a = aspectRatio();
        _projection.ortho(-a,a,-1.0,1.0,-1.0,1.0);
        _warp->updateProjection();
        _atom->updateProjection();
        _updateProjection = false;
    }
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    _warp->renderGL();
    _atom->renderGL();
    glClear(GL_DEPTH_BUFFER_BIT);
}

void PortalRenderer::resizeGL()
{
    _updateProjection = true;
}
