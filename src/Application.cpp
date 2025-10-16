#include "Application.h"
#include "Atom.h"
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
    qmlRegisterType<AtomListModel>("internal",1,0,"AtomListModel");
    qmlRegisterUncreatableType<WarpItem>("internal",1,0,"WarpItem",tr("Internal Item"));
    qmlRegisterUncreatableType<AtomItem>("internal",1,0,"AtomItem",tr("Internal Item"));
    qmlRegisterUncreatableType<Atom>("internal",1,0,"Atom",tr("Internal Model"));
}
