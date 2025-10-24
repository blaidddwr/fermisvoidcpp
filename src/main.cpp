#include "Application.h"
#include <QQmlApplicationEngine>
//TODO: change all enums to class if possible

int main(int argc,char** argv)
{
    Application app(argc,argv);
    QQmlApplicationEngine engine;
    engine.load("qrc:/qml/Main.qml");
    if (engine.rootObjects().isEmpty()) std::exit(-1);
    return app.exec();
}
