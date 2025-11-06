#ifndef PORTALRENDERER_H
#define PORTALRENDERER_H
#include "QuickRenderer.h"
#include "singleton.h"
#include <QMatrix4x4>
class GameRenderer;
#ifdef QT_DEBUG
class QOpenGLDebugLogger;
#endif

class PortalRenderer : public QuickRenderer
{
    Q_OBJECT
public:
    static PortalRenderer* instance() { return &singletonM<PortalRenderer>(); }
    PortalRenderer();
    const QMatrix4x4& projection() const { return _projection; }
    void add(GameRenderer* renderer);
    void remove(GameRenderer* renderer);
signals:
    void initRenderers();
    void projectionChanged(const QMatrix4x4& value);
protected:
    virtual void initGL() override final;
    virtual void paintGL() override final;
    virtual void resizeGL() override final;
private:
    QList<GameRenderer*> _renderers;
    QMatrix4x4 _projection;
    bool _updateProjection {true};
#ifdef QT_DEBUG
    QOpenGLDebugLogger* _logger;
#endif
};

#endif
