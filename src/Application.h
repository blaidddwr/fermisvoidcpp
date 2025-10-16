#ifndef APPLICATION_H
#define APPLICATION_H
#include <QGuiApplication>

class Application : public QGuiApplication
{
    Q_OBJECT
public:
    Application(int& argc,char** argv);
};

#endif
