#ifndef ATOMITEM_H
#define ATOMITEM_H
#include "AtomInstance.h"
#include "Latch.h"
#include "OpenGLItem.h"
class AtomRenderer;
class Molecule;

class AtomItem : public OpenGLItem
{
    Q_OBJECT
public:
    explicit AtomItem(PortalItem *parent = nullptr);
    Q_INVOKABLE void setAtom(int atomicNumber);
    void setMolecule(const Molecule& molecule);
signals:
    void radiusChanged(qreal value);
protected:
    virtual OpenGLRenderer* _createRenderer() const override final;
    virtual void _sync(OpenGLRenderer* renderer) override final;
private:
    Latch<QList<AtomInstance>> _atoms;
};

#endif
