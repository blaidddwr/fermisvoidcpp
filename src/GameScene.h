#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Latch.h"
#include "singleton.h"
#include <QMatrix4x4>
#include <QObject>
#define GAME_SCENE(cls) \
static cls& instance() { return GameScene::instance<cls>(); }
class PortalItem;

class GameScene : public QObject
{
    Q_OBJECT
public:
    template<class T> static T& instance() { return singleton<T>(); }
    GameScene();
    Q_INVOKABLE void activate();
    Q_INVOKABLE void deactivate();
protected:
    Latch<QMatrix4x4>& view() { return _view; }
    virtual void activated() = 0;
    virtual void deactivated() = 0;
    virtual void sync() = 0;
protected slots:
    virtual void onPortalCreated(PortalItem* item);
private slots:
    void onSync();
private:
    Latch<QMatrix4x4> _view;
    int _activeCount {0};
    int _active[2] {false};
};

#endif
