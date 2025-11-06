#ifndef MENUSCENE_H
#define MENUSCENE_H
#include "GameScene.h"
#include "Latch.h"
#include <QColor>
class WarpRenderer;

class MenuScene : public GameScene
{
    Q_OBJECT
public:
    GAME_SCENE(MenuScene)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor evColor READ evColor WRITE setEVColor NOTIFY evColorChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    const QColor& color() const { return _color.peek(); }
    const QColor& evColor() const { return _evColor.peek(); }
    qreal radius() const { return _radius.peek(); }
    void setColor(const QColor& value);
    void setEVColor(const QColor& value);
    void setRadius(qreal value);
signals:
    void colorChanged(const QColor& value);
    void evColorChanged(const QColor& value);
    void radiusChanged(qreal value);
protected:
    virtual void activated() override final;
    virtual void deactivated() override final;
    virtual void sync() override final;
private:
    Latch<QColor> _color;
    Latch<QColor> _evColor;
    Latch<qreal> _radius {0.0};
};

#endif
