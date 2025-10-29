#include "Atoms.h"
#include "AtomController.h"
#include <random>

AtomController::AtomController(QObject* parent):
    QObject(parent)
    ,_seed(std::random_device()())
{}

void AtomController::generateAtoms()
{
    Atoms::instance().generateAtoms(_seed);
}

void AtomController::randomizeSeed()
{
    _seed = std::random_device()();
    emit seedChanged(_seed);
}
