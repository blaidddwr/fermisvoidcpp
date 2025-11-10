#ifndef MOLECULESCENE_H
#define MOLECULESCENE_H
#include "MoleculeModel.h"
#include "CameraScene.h"

class MoleculeScene : public CameraScene
{
    Q_OBJECT
public:
    GAME_SCENE(MoleculeScene)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    using CameraScene::CameraScene;
    Q_INVOKABLE void setModel(MoleculeModel* model);
    qreal radius() const { return _radius.peek(); }
    void setRadius(qreal value);
signals:
    void radiusChanged(qreal value);
protected:
    virtual void activated() override final;
    virtual void deactivated() override final;
    virtual void sync() override final;
private slots:
    void onModelDestroyed(QObject* obj);
    void onMoleculeChanged(const Molecule& value);
private:
    Latch<QHash<QPoint,int>> _atoms;
    Latch<qreal> _radius {0.0};
    MoleculeModel* _model {nullptr};
};

#endif
