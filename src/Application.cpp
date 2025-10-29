#include "Application.h"
#include "AtomItem.h"
#include "AtomListModel.h"
#include "AtomModel.h"
#include "AtomController.h"
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
    qmlRegisterType<PortalItem>("internal",1,0,"Portal");
    qmlRegisterType<AtomController>("internal",1,0,"AtomController");
    qmlRegisterType<AtomListModel>("internal",1,0,"AtomListModel");
    qmlRegisterType<AtomModel>("internal",1,0,"AtomModel");
    qmlRegisterUncreatableType<WarpItem>("internal",1,0,"Warp",tr("Internal Item"));
    qmlRegisterUncreatableType<AtomItem>("internal",1,0,"Atom",tr("Internal Item"));
}
