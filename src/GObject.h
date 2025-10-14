#ifndef GOBJECT_H
#define GOBJECT_H
#include <QObject>

class GObject : public QObject
{
    Q_OBJECT
public:
    GObject* get(quint64 id);
    explicit GObject(QObject *parent = nullptr);
    virtual ~GObject() override;
    quint64 id() const { return _id; }
private:
    quint64 _id;
    static quint64 _nextId;
    static QList<quint64> _freeIds;
    static QHash<quint64,GObject*> _objects;
};

#endif
