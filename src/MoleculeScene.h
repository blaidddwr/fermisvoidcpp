#ifndef MOLECULESCENE_H
#define MOLECULESCENE_H
#include "Clock.h"
#include "GameScene.h"
#include "MoleculeModel.h"

class MoleculeScene : public GameScene
{
    Q_OBJECT
public:
    GAME_SCENE(MoleculeScene)
    Q_PROPERTY(qreal dx READ dx WRITE setDx NOTIFY dxChanged)
    Q_PROPERTY(qreal dy READ dy WRITE setDy NOTIFY dyChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(qreal screenScale READ screenScale NOTIFY screenScaleChanged)
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_INVOKABLE void setModel(MoleculeModel* model);
    MoleculeScene();
    qreal dx() const { return _dx; }
    qreal dy() const { return _dy; }
    qreal radius() const { return _radius.peek(); }
    qreal scale() const { return _scale; }
    qreal screenScale() const { return _screenScale; }
    qreal x() const { return _x; }
    qreal y() const { return _y; }
    void setDx(qreal value);
    void setDy(qreal value);
    void setRadius(qreal value);
    void setScale(qreal value);
    void setX(qreal value);
    void setY(qreal value);
signals:
    void dxChanged(qreal value);
    void dyChanged(qreal value);
    void radiusChanged(qreal value);
    void scaleChanged(qreal value);
    void screenScaleChanged(qreal value);
    void xChanged(qreal value);
    void yChanged(qreal value);
protected:
    virtual void activated() override final;
    virtual void deactivated() override final;
    virtual void sync() override final;
    virtual void timerEvent(QTimerEvent* event) override final;
protected slots:
    virtual void onPortalCreated(PortalItem* item) override final;
private slots:
    void onModelDestroyed(QObject* obj);
    void onMoleculeChanged(const Molecule& value);
    void updateScreenScale();
private:
    void updateView();
    Clock _clock;
    Latch<QHash<QPoint,int>> _atoms;
    Latch<qreal> _radius {0.0};
    MoleculeModel* _model {nullptr};
    qreal _dx {0.0};
    qreal _dy {0.0};
    qreal _scale {1.0};
    qreal _screenScale {1.0};
    qreal _x;
    qreal _y;
};

#endif
