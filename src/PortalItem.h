#ifndef PORTALITEM_H
#define PORTALITEM_H
#include "QuickItem.h"
#include "Latch.h"

class PortalItem : public QuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor warpColor READ warpColor WRITE setWarpColor NOTIFY warpColorChanged)
    Q_PROPERTY(QColor evColor READ evColor WRITE setEVColor NOTIFY evColorChanged)
    Q_PROPERTY(qreal warpRadius READ warpRadius WRITE setWarpRadius NOTIFY warpRadiusChanged)
public:
    PortalItem(QQuickItem* parent = nullptr);
    const QColor& warpColor() const;
    const QColor& evColor() const;
    qreal warpRadius() const;
    void setWarpColor(const QColor& value);
    void setEVColor(const QColor& value);
    void setWarpRadius(qreal value);
signals:
    void warpColorChanged(const QColor& value);
    void evColorChanged(const QColor& value);
    void warpRadiusChanged(const QColor& value);
protected:
    virtual QuickRenderer* createRenderer() override final;
    virtual void sync(QuickRenderer* renderer) override final;
    virtual void timerEvent(QTimerEvent* event) override final;
private:
    Latch<QColor> _warpColor;
    Latch<QColor> _evColor;
    Latch<qreal> _warpRadius {0.0};
};

#endif
