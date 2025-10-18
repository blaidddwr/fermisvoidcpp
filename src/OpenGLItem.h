#ifndef OPENGLITEM_H
#define OPENGLITEM_H
#include <QObject>
class OpenGLRenderer;
class PortalItem;
class PortalRenderer;

class OpenGLItem : public QObject
{
    Q_OBJECT
public:
    explicit OpenGLItem(PortalItem *parent = nullptr);
    OpenGLRenderer* createRenderer();
    OpenGLRenderer* renderer() const { return _renderer; }
    Q_INVOKABLE void activate();
    void sync();
protected:
    virtual OpenGLRenderer* _createRenderer() const = 0;
    virtual void _sync(OpenGLRenderer* renderer) = 0;
private:
    OpenGLRenderer* _renderer {nullptr};
    PortalItem* _parent;
};

#endif
