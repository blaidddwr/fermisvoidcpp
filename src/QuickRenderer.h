#ifndef QUICKRENDERER_H
#define QUICKRENDERER_H
#include <QObject>
#include <QOpenGLFunctions_4_5_Core>
#include <QSize>
class QQuickWindow;

/*
 * When creating children Qt Objects they MUST be created in the constructor and not any of the
 * virtual GL functions to avoid making children in a different thread. If they must be made in
 * the GL functions then Qt Object parent/child ownership cannot be used.
 */
class QuickRenderer : public QObject, protected QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    qreal aspectRatio() const;
    const QSize& viewport() const { return _viewport; }
    QQuickWindow* window() { return _window; }
    void setViewport(const QSize& size);
    void setWindow(QQuickWindow* window);
protected:
    virtual void initGL() {}
    virtual void paintGL() {}
    virtual void resizeGL() {}
private slots:
    void initialize();
    void paint();
private:
    QSize _viewport;
    QQuickWindow* _window {nullptr};
    bool _initialized {false};
    bool _resized {false};
};

#endif
