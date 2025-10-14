#ifndef WARPITEM_H
#define WARPITEM_H
#include "Latch.h"
#include <QColor>
#include <QObject>
class WarpRenderer;

class WarpItem : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor evColor READ evColor WRITE setEVColor NOTIFY evColorChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    explicit WarpItem(QObject *parent = nullptr);
    const QColor& color() const { return _color.peek(); }
    const QColor& evColor() const { return _evColor.peek(); }
    qreal radius() const { return _radius.peek(); }
    void setColor(const QColor& value);
    void setEVColor(const QColor& value);
    void setRadius(qreal value);
    void sync(WarpRenderer& renderer);
signals:
    void colorChanged(const QColor& value);
    void evColorChanged(const QColor& value);
    void radiusChanged(const QColor& value);
private:
    Latch<QColor> _color;
    Latch<QColor> _evColor;
    Latch<qreal> _radius {0.0};
};

#endif
