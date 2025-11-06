#include "GameRenderer.h"
#include "PortalRenderer.h"
#ifdef QT_DEBUG
#include <QOpenGLDebugLogger>
#endif

PortalRenderer::PortalRenderer()
{
#ifdef QT_DEBUG
    _logger = new QOpenGLDebugLogger(this);
    connect(
        _logger
        ,&QOpenGLDebugLogger::messageLogged
        ,[](const QOpenGLDebugMessage& msg) { qDebug() << msg; }
        );
#endif
    singletonM<PortalRenderer>(this);
}

void PortalRenderer::add(GameRenderer* renderer)
{
    Q_ASSERT(!_renderers.contains(renderer));
    _renderers.append(renderer);
}

void PortalRenderer::remove(GameRenderer* renderer)
{
    _renderers.removeOne(renderer);
}

void PortalRenderer::initGL()
{
#ifdef QT_DEBUG
    _logger->initialize();
    _logger->startLogging();
#endif
    emit initRenderers();
#ifdef QT_DEBUG
    _logger->stopLogging();
#endif
}

void PortalRenderer::paintGL()
{
#ifdef QT_DEBUG
    _logger->startLogging();
#endif
    if (_updateProjection)
    {
        _projection = QMatrix4x4();
        auto a = aspectRatio();
        _projection.ortho(-a,a,-1.0,1.0,-1.0,1.0);
        emit projectionChanged(_projection);
        _updateProjection = false;
    }
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    for (auto r: std::as_const(_renderers)) r->renderGL();
    glClear(GL_DEPTH_BUFFER_BIT);
#ifdef QT_DEBUG
    _logger->stopLogging();
#endif
}

void PortalRenderer::resizeGL()
{
    _updateProjection = true;
}
