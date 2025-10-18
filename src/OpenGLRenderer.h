#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H
#include <QObject>
#include <QOpenGLFunctions_4_5_Core>
class PortalRenderer;

class OpenGLRenderer : public QObject, protected QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit OpenGLRenderer(PortalRenderer* parent = nullptr);
    PortalRenderer* parent() const;
    virtual void initGL() {}
    virtual void renderGL() {}
    virtual void updateProjection() {}
    virtual void updateView() {}
};

#endif
