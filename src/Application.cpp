#include "Application.h"
#include "AtomController.h"
#include "AtomListModel.h"
#include "AtomModel.h"
#include "AtomRenderer.h"
#include "AtomScene.h"
#include "MenuScene.h"
#include "MoleculeModel.h"
#include "PortalItem.h"
#include "SinesRenderer.h"
#include "TransitionRenderer.h"
#include "TransitionScene.h"
#include "WarpRenderer.h"
#include <QQuickView>
#include <QSGRendererInterface>
#include <QSurfaceFormat>
#include <qqml.h>

Application::Application(int& argc,char** argv):
    QGuiApplication(argc,argv)
{
    QQuickView::setGraphicsApi(QSGRendererInterface::OpenGL);
    auto format = QSurfaceFormat();
    format.setVersion(4,5);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    QSurfaceFormat::setDefaultFormat(format);
    qmlRegisterType<PortalItem>("internal",1,0,"Portal");
    qmlRegisterType<AtomController>("internal",1,0,"AtomController");
    qmlRegisterType<AtomModel>("internal",1,0,"AtomModel");
    qmlRegisterType<AtomListModel>("internal",1,0,"AtomListModel");
    qmlRegisterType<MoleculeModel>("internal",1,0,"MoleculeModel");
    qmlRegisterSingletonInstance("internal",1,0,"TransitionScene",&TransitionScene::instance());
    qmlRegisterSingletonInstance("internal",1,0,"MenuScene",&MenuScene::instance());
    qmlRegisterSingletonInstance("internal",1,0,"AtomScene",&AtomScene::instance());
}

void Application::registerPortal(PortalItem* item)
{
    Q_ASSERT(item);
    Q_ASSERT(!_portal);
    _portal = item;
    connect(item,&PortalItem::rendererCreated,this,&Application::onPortalRendererCreated);
    emit portalCreated(item);
}

void Application::onPortalRendererCreated(PortalRenderer* renderer)
{
    SinesRenderer::create(renderer);
    WarpRenderer::create(renderer);
    TransitionRenderer::create(renderer);
    AtomRenderer::create(renderer);
    SinesRenderer::instance().use();
}
