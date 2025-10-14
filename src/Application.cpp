#include "Application.h"
#include "AtomItem.h"
#include "AtomListModel.h"
#include "GameController.h"
#include "PortalItem.h"
#include "WarpItem.h"
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
    qmlRegisterSingletonInstance("internal",1,0,"Game",&GameController::instance());
    qmlRegisterType<PortalItem>("internal",1,0,"Portal");
    qmlRegisterUncreatableType<WarpItem>("internal",1,0,"Warp",tr("Member Singleton"));
    qmlRegisterUncreatableType<AtomItem>("internal",1,0,"Atom",tr("Member Singleton"));
    qmlRegisterType<AtomListModel>("internal",1,0,"AtomListModel");
}
