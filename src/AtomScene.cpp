#include "AtomRenderer.h"
#include "AtomScene.h"
#include "Atoms.h"
#include "WarpRenderer.h"

void AtomScene::setAtomicNumber(int value)
{
    if (_atomicNumber != value)
    {
        _atomicNumber = value;
        if (value == -1) _atom.set() = {};
        else
        {
            Q_ASSERT(value > 0);
            Q_ASSERT(value <= Atoms::instance().size());
            _atom.set() = {{{0,0},value}};
        }
        emit atomicNumberChanged(value);
    }
}

void AtomScene::setRadius(qreal value)
{
    _radius = value;
}

/*
 * TODO: move to MoleculeScene, once implemented
void AtomItem::setModel(MoleculeModel* model)
{
    if (!model || model->molecule().isEmpty())
    {
        _atoms.set() = {};
        return;
    }
    _atoms.set() = model->molecule().atoms();
    setRadius(model.radius()+0.8);
    setScale((model.radius()+0.8)/0.8);
    setOffset(model.center());
}
*/

void AtomScene::activated()
{
    WarpRenderer::instance().use();
    AtomRenderer::instance().use();
    _radius.set();
    _atom.set();
}

void AtomScene::deactivated()
{
    AtomRenderer::instance().release();
    WarpRenderer::instance().release();
}

void AtomScene::sync()
{
    if (_radius.updated()) WarpRenderer::instance().setRadius(ActualRadius*_radius.get());
    if (_atom.updated()) AtomRenderer::instance().setAtoms(_atom.get());
}
