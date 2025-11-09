#include "Application.h"
#include "PortalItem.h"
#include "PortalRenderer.h"
#include <QQuickWindow>

PortalItem::PortalItem(QQuickItem* parent):
    QuickItem(parent)
{
    auto app = qobject_cast<Application*>(QGuiApplication::instance());
    Q_ASSERT(app);
    app->registerPortal(this);
    startTimer(16);
    singletonM<PortalItem>(this);
}

QuickRenderer* PortalItem::createRenderer()
{
    auto ret = new PortalRenderer;
    emit rendererCreated(ret);
    return ret;
}

void PortalItem::sync(QuickRenderer* renderer)
{
    auto pr = qobject_cast<PortalRenderer*>(renderer);
    Q_ASSERT(pr);
    emit syncRenderers(pr);
}

void PortalItem::timerEvent(QTimerEvent* event)
{
    if (window()) window()->update();
    event->accept();
}
