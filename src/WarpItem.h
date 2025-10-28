#ifndef WARPITEM_H
#define WARPITEM_H
#include "Latch.h"
#include <QColor>
#include <QObject>
class WarpRenderer;
//TODO: Transform this into the main menu renderer, separate the warp renderer into its own thing
// because it will be reused for other renderers (like the atom renderer)
//TODO: Make a new transition renderer that is used for transitioning between renderers, this will
//expose itself to QML so it can be used to be in sync with new QML page transitions on the main
//stack view

class WarpItem : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor evColor READ evColor WRITE setEVColor NOTIFY evColorChanged)
    Q_PROPERTY(qreal actualRadius READ actualRadius NOTIFY actualRadiusChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    explicit WarpItem(QObject *parent = nullptr);
    const QColor& color() const { return _color.peek(); }
    const QColor& evColor() const { return _evColor.peek(); }
    qreal actualRadius() const { return _actualRadius.peek(); }
    qreal radius() const { return _radius.peek(); }
    void setActualRadius(qreal value);
    void setColor(const QColor& value);
    void setEVColor(const QColor& value);
    void setRadius(qreal value);
    void sync(WarpRenderer& renderer);
signals:
    void actualRadiusChanged(qreal value);
    void colorChanged(const QColor& value);
    void evColorChanged(const QColor& value);
    void radiusChanged(qreal value);
private:
    Latch<QColor> _color;
    Latch<QColor> _evColor;
    Latch<qreal> _actualRadius {0.0};
    Latch<qreal> _radius {0.0};
};

#endif
