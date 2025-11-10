#include "CameraScene.h"
#include <QTimerEvent>

CameraScene::CameraScene()
{
    startTimer(16);
}

void CameraScene::setCameraTarget(qreal x,qreal y,qreal z,int duration)
{
    _target.time = qreal(duration)/1000.0;
    _target.dx = (x-_x)/_target.time;
    _target.dy = (y-_y)/_target.time;
    _target.dz = (z-_z)/_target.time;
}

void CameraScene::setDx(qreal value)
{
    clearTargeting();
    if (_dx != value)
    {
        _dx = value;
        emit dxChanged(value);
    }
}

void CameraScene::setDy(qreal value)
{
    clearTargeting();
    if (_dy != value)
    {
        _dy = value;
        emit dyChanged(value);
    }
}

void CameraScene::setDz(qreal value)
{
    clearTargeting();
    if (_dz != value)
    {
        _dz = value;
        emit dzChanged(value);
    }
}

void CameraScene::setViewAngle(qreal value)
{
    Q_ASSERT(value >= 0.0);
    Q_ASSERT(value <= 90.0);
    clearTargeting();
    clearMovement();
    if (_viewAngle != value)
    {
        _viewAngle = value;
        setScale(1.0/(_z*qSin(_viewAngle*M_PI/180.0)));
        updateView();
        emit viewAngleChanged(value);
    }
}

void CameraScene::setX(qreal value)
{
    clearTargeting();
    clearMovement();
    _setX(value);
}

void CameraScene::setY(qreal value)
{
    clearTargeting();
    clearMovement();
    _setY(value);
}

void CameraScene::setZ(qreal value)
{
    clearTargeting();
    clearMovement();
    _setZ(value);
}

void CameraScene::timerEvent(QTimerEvent* event)
{
    auto dt = _clock.mark();
    if (!_target.time)
    {
        if (_dx) _setX(_x+(_dx*dt/_scale));
        if (_dy) _setY(_y+(_dy*dt/_scale));
        if (_dz) _setZ(_z+(_dz*dt));
    }
    else
    {
        if (_target.time < dt) dt = _target.time;
        if (_target.dx) _setX(_x+(_target.dx*dt));
        if (_target.dy) _setY(_y+(_target.dy*dt));
        if (_target.dz) _setZ(_z+(_target.dz*dt));
        _target.time -= dt;
        if (_target.time < 0.0) _target.time = 0.0;
    }
    event->accept();
}

void CameraScene::_setX(qreal value)
{
    if (_x != value)
    {
        _x = value;
        updateView();
        emit xChanged(value);
    }
}

void CameraScene::_setY(qreal value)
{
    if (_y != value)
    {
        _y = value;
        updateView();
        emit yChanged(value);
    }
}

void CameraScene::_setZ(qreal value)
{
    if (value < 0.1) value = 0.1;
    if (_z != value)
    {
        _z = value;
        setScale(1.0/(_z*qSin(_viewAngle*M_PI/180.0)));
        updateView();
        emit zChanged(value);
    }
}

void CameraScene::clearMovement()
{
    setDx(0.0);
    setDy(0.0);
    setDz(0.0);
}

void CameraScene::clearTargeting()
{
    _target.time = 0.0;
}

void CameraScene::setScale(qreal value)
{
    if (_scale != value)
    {
        _scale = value;
        emit scaleChanged(value);
    }
}

void CameraScene::updateView()
{
    auto& view = GameScene::view().set();
    view.setToIdentity();
    view.scale(_scale);
    view.translate(-_x,-_y);
}
