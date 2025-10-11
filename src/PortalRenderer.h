#ifndef PORTALRENDERER_H
#define PORTALRENDERER_H
#include "QuickRenderer.h"
#include <QMatrix4x4>
class WarpRenderer;

class PortalRenderer : public QuickRenderer
{
    Q_OBJECT
public:
    PortalRenderer();
    void setWarpColor(const QColor& value);
    void setEVColor(const QColor& value);
    void setWarpRadius(qreal value);
    const QMatrix4x4& view() const;
    const QMatrix4x4& projection() const;
    qreal scale() const;
protected:
    virtual void initGL() override final;
    virtual void paintGL() override final;
    virtual void resizeGL() override final;
private:
    WarpRenderer* _warp {nullptr};
    QMatrix4x4 _view;
    QMatrix4x4 _projection;
    bool _updateProjection {true};
    qreal _scale {1.0};
};

#endif
