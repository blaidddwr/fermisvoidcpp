#ifndef APPLICATION_H
#define APPLICATION_H
#include <QGuiApplication>
class PortalItem;
class PortalRenderer;

class Application : public QGuiApplication
{
    Q_OBJECT
public:
    Application(int& argc,char** argv);
    void registerPortal(PortalItem* item);
signals:
    void portalCreated(PortalItem* item);
private slots:
    void onPortalRendererCreated(PortalRenderer* renderer);
private:
    PortalItem* _portal {nullptr};
};

#endif
