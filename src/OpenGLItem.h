#ifndef OPENGLITEM_H
#define OPENGLITEM_H
#include <QObject>
#include <QPointF>
class OpenGLRenderer;
class PortalItem;
class PortalRenderer;

class OpenGLItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF offset READ offset NOTIFY offsetChanged)
    Q_PROPERTY(qreal radius READ radius NOTIFY radiusChanged)
    Q_PROPERTY(qreal scale READ scale NOTIFY scaleChanged)
public:
    explicit OpenGLItem(PortalItem *parent = nullptr);
    OpenGLRenderer* createRenderer();
    OpenGLRenderer* renderer() const { return _renderer; }
    Q_INVOKABLE void activate();
    const QPointF offset() const { return _offset; }
    qreal radius() const { return _radius; }
    qreal scale() const { return _scale; }
    void sync();
signals:
    void offsetChanged(const QPointF& value);
    void radiusChanged(qreal value);
    void scaleChanged(qreal value);
protected:
    virtual OpenGLRenderer* _createRenderer() const = 0;
    virtual void _sync(OpenGLRenderer* renderer) = 0;
    void setOffset(const QPointF& value);
    void setRadius(qreal value);
    void setScale(qreal value);
private:
    OpenGLRenderer* _renderer {nullptr};
    PortalItem* _parent;
    QPointF _offset {0.0,0.0};
    qreal _radius {0.0};
    qreal _scale {1.0};
};

#endif
