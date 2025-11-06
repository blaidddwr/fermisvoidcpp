#ifndef ATOMS_H
#define ATOMS_H
#include "GameObject.h"
#include "singleton.h"
class Atom;

class Atoms : public GameObject
{
    Q_OBJECT
public:
    enum class Direction {
        Top
        ,Right
        ,Bottom
        ,Left
    };
    static Atoms& instance() { return singleton<Atoms>(); }
    Atoms();
    virtual ~Atoms() override;
    bool canBond(int atomicNumber0,int atomicNumber1,Direction direction);
    const Atom& get(int atomicNumber) const;
    int size() const { return _atoms.size(); }
    void generateAtoms(int seed);
signals:
    void atomsAboutToReset();
    void atomsReset();
private:
    QList<Atom*> _atoms;
};

#endif
