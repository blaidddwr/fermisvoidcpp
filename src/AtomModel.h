#ifndef ATOMMODEL_H
#define ATOMMODEL_H
#include <QColor>
#include <QObject>
class Atom;

class AtomModel : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)
    Q_PROPERTY(int atomicNumber READ atomicNumber WRITE setAtomicNumber NOTIFY atomicNumberChanged)
    Q_PROPERTY(int charge READ charge NOTIFY chargeChanged)
    Q_PROPERTY(qreal mass READ mass NOTIFY massChanged)
    explicit AtomModel(QObject *parent = nullptr);
    const QColor& color() const;
    int atomicNumber() const;
    int charge() const;
    qreal mass() const;
    void setAtomicNumber(int value);
signals:
    void atomicNumberChanged(int value);
    void chargeChanged(int value);
    void colorChanged(const QColor& value);
    void massChanged(qreal value);
private:
    const Atom* _atom {nullptr};
};

#endif
