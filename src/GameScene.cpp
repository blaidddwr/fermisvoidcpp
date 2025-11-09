#include "Application.h"
#include "GameScene.h"
#include "PortalItem.h"

GameScene::GameScene():
    QObject(QGuiApplication::instance())
{
    auto app = qobject_cast<Application*>(parent());
    Q_ASSERT(app);
    connect(app,&Application::portalCreated,this,&GameScene::onPortalCreated);
}

void GameScene::activate()
{
    _activeCount++;
}

void GameScene::deactivate()
{
    _activeCount--;
}

void GameScene::onPortalCreated(PortalItem* item)
{
    connect(item,&PortalItem::syncRenderers,this,&GameScene::onSync);
}

void GameScene::onSync()
{
    _active[0] = (_activeCount > 0);
    if (_active[0] != _active[1])
    {
        _active[0] ? activated() : deactivated();
        _active[1] = _active[0];
    }
    if (_active[0]) sync();
}
