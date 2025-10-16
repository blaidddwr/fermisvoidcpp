#ifndef PORTALRENDERER_H
#define PORTALRENDERER_H
#include "QuickRenderer.h"
#include <QMatrix4x4>
class AtomRenderer;
class WarpRenderer;
class SinesRenderer;

class PortalRenderer : public QuickRenderer
{
    Q_OBJECT
public:
    PortalRenderer();
    AtomRenderer& atom() { return *_atom; }
    SinesRenderer& sines() { return *_sines; }
    WarpRenderer& warp() { return *_warp; }
    const QMatrix4x4& projection() const { return _projection; }
    const QMatrix4x4& view() const { return _view; }
    qreal scale() const { return _scale; }
protected:
    virtual void initGL() override final;
    virtual void paintGL() override final;
    virtual void resizeGL() override final;
private:
    AtomRenderer* _atom {nullptr};
    QMatrix4x4 _projection;
    QMatrix4x4 _view;
    SinesRenderer* _sines;
    WarpRenderer* _warp {nullptr};
    bool _updateProjection {true};
    qreal _scale {1.0};
};

#endif
