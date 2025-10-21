#ifndef OPENGLITEM_H
#define OPENGLITEM_H
#include <QObject>
class OpenGLRenderer;
class PortalItem;
class PortalRenderer;

class OpenGLItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal radius READ radius NOTIFY radiusChanged)
public:
    explicit OpenGLItem(PortalItem *parent = nullptr);
    OpenGLRenderer* createRenderer();
    OpenGLRenderer* renderer() const { return _renderer; }
    Q_INVOKABLE void activate();
    qreal radius() const { return _radius; }
    void sync();
signals:
    void radiusChanged(qreal value);
protected:
    virtual OpenGLRenderer* _createRenderer() const = 0;
    virtual void _sync(OpenGLRenderer* renderer) = 0;
    void setRadius(qreal value);
private:
    OpenGLRenderer* _renderer {nullptr};
    PortalItem* _parent;
    qreal _radius {0.0};
};

#endif
