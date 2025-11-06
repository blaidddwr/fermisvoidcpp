#include "GameObject.h"
#include <QHash>

QHash<quint64,GameObject*> GameObject::_objects;
QList<quint64> GameObject::_freeIds;
quint64 GameObject::_nextId {0};

GameObject* GameObject::get(quint64 id)
{
    return _objects.value(id,nullptr);
}

GameObject::GameObject(QObject *parent):
    QObject(parent)
{
    if (!_freeIds.isEmpty()) _id = _freeIds.takeLast();
    else _id = _nextId++;
    _objects.insert(_id,this);
}

GameObject::~GameObject()
{
    Q_ASSERT(_objects.contains(_id));
    _objects.remove(_id);
    _freeIds.append(_id);
}
