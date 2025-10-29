#ifndef ATOMCONTROLLER_H
#define ATOMCONTROLLER_H
#include <QObject>

class AtomController : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(int seed READ seed NOTIFY seedChanged)
    explicit AtomController(QObject* parent = nullptr);
    Q_INVOKABLE void generateAtoms();
    Q_INVOKABLE void randomizeSeed();
    int seed() const { return _seed; }
signals:
    void seedChanged(int value);
private:
    int _seed;
};

#endif
