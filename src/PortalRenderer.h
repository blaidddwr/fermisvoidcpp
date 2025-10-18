#ifndef PORTALRENDERER_H
#define PORTALRENDERER_H
#include "Latch.h"
#include "QuickRenderer.h"
#include <QMatrix4x4>
class OpenGLRenderer;
class WarpRenderer;
class SinesRenderer;

class PortalRenderer : public QuickRenderer
{
    Q_OBJECT
public:
    PortalRenderer(const QList<OpenGLRenderer*>& renderers);
    SinesRenderer& sines() { return *_sines; }
    WarpRenderer& warp() { return *_warp; }
    const QMatrix4x4& projection() const { return _projection; }
    const QMatrix4x4& view() const { return _view; }
    qreal scale() const { return _scale; }
    void setActive(OpenGLRenderer* renderer);
protected:
    virtual void initGL() override final;
    virtual void paintGL() override final;
    virtual void resizeGL() override final;
private:
    Latch<OpenGLRenderer*> _active {nullptr};
    QList<OpenGLRenderer*> _renderers;
    QMatrix4x4 _projection;
    QMatrix4x4 _view;
    SinesRenderer* _sines;
    WarpRenderer* _warp {nullptr};
    bool _updateProjection {true};
    qreal _scale {1.0};
};

#endif
