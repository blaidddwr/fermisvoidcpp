#ifndef TRANSITIONSCENE_H
#define TRANSITIONSCENE_H
#include "GameScene.h"
#include "Latch.h"
#include <QColor>

class TransitionScene : public GameScene
{
    Q_OBJECT
public:
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    GAME_SCENE(TransitionScene)
    const QColor& color() const { return _color.peek(); }
    qreal x() const { return _x.peek(); }
    void setColor(const QColor& value);
    void setX(qreal value);
signals:
    void colorChanged(const QColor& value);
    void xChanged(qreal value);
protected:
    virtual void activated() override final;
    virtual void deactivated() override final;
    virtual void sync() override final;
private:
    Latch<QColor> _color;
    Latch<qreal> _x;
};

#endif
