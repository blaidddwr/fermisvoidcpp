#include "AtomRenderer.h"
#include "MoleculeScene.h"
#include "WarpRenderer.h"

void MoleculeScene::setModel(MoleculeModel* model)
{
    if (_model)
    {
        disconnect(_model,&MoleculeModel::moleculeChanged,this,&MoleculeScene::onMoleculeChanged);
        disconnect(_model,&QObject::destroyed,this,&MoleculeScene::onModelDestroyed);
    }
    _model = model;
    if (_model)
    {
        connect(_model,&MoleculeModel::moleculeChanged,this,&MoleculeScene::onMoleculeChanged);
        connect(_model,&QObject::destroyed,this,&MoleculeScene::onModelDestroyed);
        _atoms = _model->molecule().atoms();
    }
    else _atoms.set() = {};
}

void MoleculeScene::setRadius(qreal value)
{
    _radius = value;
}

void MoleculeScene::activated()
{
    WarpRenderer::instance().use();
    AtomRenderer::instance().use();
    view().set();
    _atoms.set();
}

void MoleculeScene::deactivated()
{
    AtomRenderer::instance().release();
    WarpRenderer::instance().release();
}

void MoleculeScene::sync()
{
    auto& warp = WarpRenderer::instance();
    auto& atom = AtomRenderer::instance();
    if (view().updated())
    {
        warp.setView(view().get());
        warp.setScale(scale());
        atom.setView(view().get());
    }
    if (_radius.updated()) warp.setRadius(_radius.get());
    if (_atoms.updated()) atom.setAtoms(_atoms.get());
}

void MoleculeScene::onModelDestroyed(QObject* obj)
{
    if (_model == obj) setModel(nullptr);
}

void MoleculeScene::onMoleculeChanged(const Molecule& value)
{
    _atoms = value.atoms();
}
