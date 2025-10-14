#include "Atoms.h"
#include "GameController.h"
#include <QGuiApplication>
#include <random>

GameController* GameController::_instance {nullptr};

GameController& GameController::instance()
{
    if (!_instance) _instance = new GameController;
    return *_instance;
}

void GameController::start()
{
    std::random_device rd;
    Atoms::instance().generateAtoms(rd());
}

GameController::GameController():
    QObject(QGuiApplication::instance())
{}
