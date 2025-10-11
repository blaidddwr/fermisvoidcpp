#include "QuickRenderer.h"
#include <QQuickOpenGLUtils>
#include <QQuickWindow>
#include <QThread>

qreal QuickRenderer::aspectRatio() const
{
    return qreal(_viewport.width())/qreal(_viewport.height());
}

const QSize& QuickRenderer::viewport() const
{
    return _viewport;
}

QQuickWindow* QuickRenderer::window()
{
    return _window;
}

void QuickRenderer::setViewport(const QSize& size)
{
    if (_viewport != size)
    {
        _viewport = size;
        _resized = true;
    }
}

void QuickRenderer::setWindow(QQuickWindow* window)
{
    if (_window)
    {
        disconnect(window,&QQuickWindow::beforeRendering,this,&QuickRenderer::initialize);
        disconnect(window,&QQuickWindow::beforeRenderPassRecording,this,&QuickRenderer::paint);
    }
    _window = window;
    if (_window)
    {
        connect(
            window
            ,&QQuickWindow::beforeRendering
            ,this
            ,&QuickRenderer::initialize
            ,Qt::DirectConnection
            );
        connect(
            window
            ,&QQuickWindow::beforeRenderPassRecording
            ,this
            ,&QuickRenderer::paint
            ,Qt::DirectConnection
            );
    }
}

void QuickRenderer::initGL() {}

void QuickRenderer::paintGL() {}

void QuickRenderer::resizeGL() {}

void QuickRenderer::initialize()
{
    if (!_initialized)
    {
        initializeOpenGLFunctions();
        initGL();
        _initialized = true;
    }
}

void QuickRenderer::paint()
{
    Q_ASSERT(_window);
    _window->beginExternalCommands();
    QQuickOpenGLUtils::resetOpenGLState();
    glViewport(0,0,_viewport.width(),_viewport.height());
    if (_resized)
    {
        resizeGL();
        _resized = false;
    }
    paintGL();
    _window->endExternalCommands();
}
