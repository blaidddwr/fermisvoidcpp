#ifndef CAMERASCENE_H
#define CAMERASCENE_H
#include "GameScene.h"
#include "Clock.h"//TODO change fMin/fMax to qMin/qMax

class CameraScene : public GameScene
{
    Q_OBJECT
public:
    Q_PROPERTY(qreal dx READ dx WRITE setDx NOTIFY dxChanged)
    Q_PROPERTY(qreal dy READ dy WRITE setDy NOTIFY dyChanged)
    Q_PROPERTY(qreal dz READ dz WRITE setDz NOTIFY dzChanged)
    Q_PROPERTY(qreal scale READ scale NOTIFY scaleChanged)
    Q_PROPERTY(qreal viewAngle READ viewAngle WRITE setViewAngle NOTIFY viewAngleChanged)
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qreal z READ z WRITE setZ NOTIFY zChanged)
    CameraScene();
    Q_INVOKABLE void setCameraTarget(qreal x,qreal y,qreal z,int duration);
    qreal dx() const { return _dx; }
    qreal dy() const { return _dy; }
    qreal dz() const { return _dz; }
    qreal scale() const { return _scale; }
    qreal viewAngle() const { return _viewAngle; }
    qreal x() const { return _x; }
    qreal y() const { return _y; }
    qreal z() const { return _z; }
    void setDx(qreal value);
    void setDy(qreal value);
    void setDz(qreal value);
    void setViewAngle(qreal value);
    void setX(qreal value);
    void setY(qreal value);
    void setZ(qreal value);
signals:
    void dxChanged(qreal value);
    void dyChanged(qreal value);
    void dzChanged(qreal value);
    void scaleChanged(qreal value);
    void viewAngleChanged(qreal value);
    void xChanged(qreal value);
    void yChanged(qreal value);
    void zChanged(qreal value);
protected:
    virtual void timerEvent(QTimerEvent* event) override final;
private:
    struct Target
    {
        qreal dx {0.0};
        qreal dy {0.0};
        qreal dz {1.0};
        qreal time {0.0};
    };
    void _setX(qreal value);
    void _setY(qreal value);
    void _setZ(qreal value);
    void clearMovement();
    void clearTargeting();
    void setScale(qreal value);
    void updateView();
    Clock _clock;
    Target _target;
    qreal _dx {0.0};
    qreal _dy {0.0};
    qreal _dz {1.0};
    qreal _scale {1.0};
    qreal _viewAngle {90.0};
    qreal _x;
    qreal _y;
    qreal _z;
};

#endif
