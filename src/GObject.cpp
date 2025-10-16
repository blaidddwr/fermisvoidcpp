#include "GObject.h"
#include <QHash>

QHash<quint64,GObject*> GObject::_objects;
QList<quint64> GObject::_freeIds;
quint64 GObject::_nextId {0};

GObject* GObject::get(quint64 id)
{
    return _objects.value(id,nullptr);
}

GObject::GObject(QObject *parent):
    QObject(parent)
{
    if (!_freeIds.isEmpty()) _id = _freeIds.takeLast();
    else _id = _nextId++;
    _objects.insert(_id,this);
}

GObject::~GObject()
{
    Q_ASSERT(_objects.contains(_id));
    _objects.remove(_id);
    _freeIds.append(_id);
}
