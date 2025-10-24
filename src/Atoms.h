#ifndef ATOMS_H
#define ATOMS_H
#include "GObject.h"
class Atom;

class Atoms : public GObject
{
    Q_OBJECT
public:
    enum class Direction {
        Top
        ,Right
        ,Bottom
        ,Left
    };
    static Atoms& instance();
    bool canBond(int atomicNumber0,int atomicNumber1,Direction direction);
    const Atom& get(int atomicNumber) const;
    int size() const { return _atoms.size(); }
    void generateAtoms(int seed);
signals:
    void atomsAboutToReset();
    void atomsReset();
private:
    Atoms();
    static Atoms* _instance;
    QList<Atom*> _atoms;
};

#endif
