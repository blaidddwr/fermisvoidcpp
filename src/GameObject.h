#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <QObject>

class GameObject : public QObject
{
    Q_OBJECT
public:
    static GameObject* get(quint64 id);
    explicit GameObject(QObject *parent = nullptr);
    virtual ~GameObject() override;
    quint64 id() const { return _id; }
private:
    quint64 _id;
    static QHash<quint64,GameObject*> _objects;
    static QList<quint64> _freeIds;
    static quint64 _nextId;
};

#endif
