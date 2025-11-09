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

void AtomScene::activated()
{
    WarpRenderer::instance().use();
    AtomRenderer::instance().use();
    view().set();
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
    auto& warp = WarpRenderer::instance();
    auto& atom = AtomRenderer::instance();
    if (view().updated())
    {
        warp.setView(view().get());
        warp.setScale(1.0);
        atom.setView(view().get());
    }
    if (_radius.updated()) warp.setRadius(ActualRadius*_radius.get());
    if (_atom.updated()) atom.setAtoms(_atom.get());
}
