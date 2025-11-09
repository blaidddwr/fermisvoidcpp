#ifndef ATOMSCENE_H
#define ATOMSCENE_H
#include "Latch.h"
#include "GameScene.h"
#include <QHash>

class AtomScene : public GameScene
{
    Q_OBJECT
public:
    static constexpr qreal ActualRadius {0.8};
    GAME_SCENE(AtomScene)
    Q_PROPERTY(int atomicNumber READ atomicNumber WRITE setAtomicNumber NOTIFY atomicNumberChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    int atomicNumber() const { return _atomicNumber; }
    qreal radius() const { return _radius.peek(); }
    void setAtomicNumber(int value);
    void setRadius(qreal value);
signals:
    void atomicNumberChanged(int value);
    void radiusChanged(int value);
protected:
    virtual void activated() override final;
    virtual void deactivated() override final;
    virtual void sync() override final;
private:
    Latch<QHash<QPoint,int>> _atom;
    Latch<qreal> _radius {0.0};
    int _atomicNumber {-1};
};

#endif
