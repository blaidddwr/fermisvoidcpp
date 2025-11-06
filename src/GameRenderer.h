#ifndef GAMERENDERER_H
#define GAMERENDERER_H
#include "singleton.h"
#include <QMatrix4x4>
#include <QObject>
#include <QOpenGLFunctions_4_5_Core>
#define GAME_RENDERER(cls) \
static cls& instance() { return GameRenderer::instance<cls>(); } \
static void create(PortalRenderer* parent) { singletonM<cls>(new cls(parent)); }
class PortalRenderer;

class GameRenderer : public QObject, protected QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    GameRenderer(PortalRenderer* parent);
    const QMatrix4x4& projection();
    const QMatrix4x4& view();
    virtual void renderGL() {}
    void release();
    void setView(const QMatrix4x4& value);
    void updateProjection() { _projectionUpdated = true; }
    void use();
protected:
    template<class T> static T& instance() { return singletonM<T>(); }
    bool projectionUpdated() const { return _projectionUpdated; }
    bool viewUpdated() const { return _viewUpdated; }
protected slots:
    virtual void initGL() {}
private slots:
    void onProjectionChanged();
private:
    QMatrix4x4 _view;
    bool _projectionUpdated {true};
    bool _viewUpdated {true};
    int _retained {0};
};

#endif
