#include "QuickItem.h"
#include "QuickRenderer.h"
#include <QRunnable>
#include <QQuickWindow>

class QuickItemCleanupJob : public QRunnable
{
public:
    QuickItemCleanupJob(QuickRenderer* renderer): _renderer(renderer) {}
    virtual void run() override final
    {
        delete _renderer;
    }
private:
    QuickRenderer* _renderer;
};

QuickItem::QuickItem(QQuickItem* parent):
    QQuickItem(parent)
{
    connect(this,&QQuickItem::windowChanged,this,&QuickItem::onWindowChanged);
}

void QuickItem::releaseResources()
{
    Q_ASSERT(window());
    if (_renderer)
    {
        window()->scheduleRenderJob(
            new QuickItemCleanupJob(_renderer)
            ,QQuickWindow::BeforeSynchronizingStage
            );
        _renderer = nullptr;
    }
}

void QuickItem::cleanup()
{
    delete _renderer;
    _renderer = nullptr;
}

void QuickItem::onWindowChanged(QQuickWindow* window)
{
    if (window)
    {
        connect(window,&QQuickWindow::beforeSynchronizing,this,&QuickItem::synchronize);
        connect(window,&QQuickWindow::sceneGraphInvalidated,this,&QuickItem::cleanup);
        synchronize();
        _renderer->setWindow(window);
    }
}

void QuickItem::synchronize()
{
    if (!_renderer) _renderer = createRenderer();
    _renderer->setViewport(window()->size()*window()->devicePixelRatio());
    sync(_renderer);
}
