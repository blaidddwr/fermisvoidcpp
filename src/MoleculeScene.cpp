#include "AtomRenderer.h"
#include "MoleculeScene.h"
#include "PortalItem.h"
#include "WarpRenderer.h"

MoleculeScene::MoleculeScene()
{
    startTimer(16);
}

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

void MoleculeScene::setDx(qreal value)
{
    if (_dx != value)
    {
        _dx = value;
        emit dxChanged(value);
    }
}

void MoleculeScene::setDy(qreal value)
{
    if (_dy != value)
    {
        _dy = value;
        emit dyChanged(value);
    }
}

void MoleculeScene::setRadius(qreal value)
{
    _radius = value;
}

void MoleculeScene::setScale(qreal value)
{
    if (_scale != value)
    {
        _scale = value;
        updateScreenScale();
        updateView();
        emit scaleChanged(value);
    }
}

void MoleculeScene::setX(qreal value)
{
    if (_x != value)
    {
        _x = value;
        updateView();
        emit xChanged(value);
    }
}

void MoleculeScene::setY(qreal value)
{
    if (_y != value)
    {
        _y = value;
        updateView();
        emit yChanged(value);
    }
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
        warp.setScale(_scale);
        atom.setView(view().get());
    }
    if (_radius.updated()) warp.setRadius(_radius.get());
    if (_atoms.updated()) atom.setAtoms(_atoms.get());
}

void MoleculeScene::timerEvent(QTimerEvent* event)
{
    auto dt = _clock.mark();
    if (_dx) setX(_x+(_dx*dt));
    if (_dy) setY(_y+(_dy*dt));
    event->accept();
}

void MoleculeScene::onPortalCreated(PortalItem* item)
{
    connect(item,&PortalItem::heightChanged,this,&MoleculeScene::updateScreenScale);
    GameScene::onPortalCreated(item);
}

void MoleculeScene::onModelDestroyed(QObject* obj)
{
    if (_model == obj) setModel(nullptr);
}

void MoleculeScene::onMoleculeChanged(const Molecule& value)
{
    _atoms = value.atoms();
}

void MoleculeScene::updateScreenScale()
{
    qreal nss = _scale*PortalItem::instance()->height()/2.0;
    if (_screenScale != nss)
    {
        _screenScale = nss;
        emit screenScaleChanged(nss);
    }
}

void MoleculeScene::updateView()
{
    auto& view = GameScene::view().set();
    view.setToIdentity();
    view.scale(_scale);
    view.translate(-_x,-_y);
}
