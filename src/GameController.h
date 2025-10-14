#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QObject>

class GameController : public QObject
{
    Q_OBJECT
public:
    static GameController& instance();
public slots:
    void start();
private:
    GameController();
    static GameController* _instance;
};

#endif
