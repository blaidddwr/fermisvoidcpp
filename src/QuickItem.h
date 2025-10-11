#ifndef QUICKITEM_H
#define QUICKITEM_H
#include <QQuickItem>
class QuickRenderer;

class QuickItem : public QQuickItem
{
    Q_OBJECT
public:
    explicit QuickItem(QQuickItem* parent = nullptr);
    virtual void releaseResources() override final;
protected:
    virtual QuickRenderer* createRenderer() = 0;
    virtual void sync(QuickRenderer* renderer) = 0;
private slots:
    void cleanup();
    void onWindowChanged(QQuickWindow* window);
    void synchronize();
private:
    QuickRenderer* _renderer {nullptr};
};

#endif
