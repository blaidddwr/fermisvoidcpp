#include "Application.h"
#include "PortalItem.h"
#include <QQmlApplicationEngine>
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
    _engine = new QQmlApplicationEngine(this);
    _engine->load("qrc:/qml/Main.qml");
    if (_engine->rootObjects().isEmpty())
    {
        std::exit(-1);
    }
}
