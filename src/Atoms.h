#ifndef ATOMS_H
#define ATOMS_H
#include "GObject.h"
class Atom;

class Atoms : public GObject
{
    Q_OBJECT
public:
    static Atoms& instance();
    void generateAtoms(int seed);
    int size() const { return _atoms.size(); }
    const Atom& get(int atomicNumber) const;
signals:
    void atomsAboutToReset();
    void atomsReset();
private:
    Atoms();
    static Atoms* _instance;
    QList<Atom*> _atoms;
};

#endif
