#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H
#include <QObject>
#include <QOpenGLFunctions_4_5_Core>
class PortalRenderer;

class OpenGLRenderer : public QObject, protected QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit OpenGLRenderer(PortalRenderer* parent);
    PortalRenderer* parent() const { return _parent; }
private:
    PortalRenderer* _parent;
};

#endif
