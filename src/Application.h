#ifndef APPLICATION_H
#define APPLICATION_H
#include <QGuiApplication>
class QQmlApplicationEngine;

class Application : public QGuiApplication
{
public:
    Application(int& argc,char** argv);
private:
    QQmlApplicationEngine* _engine;
};

#endif
