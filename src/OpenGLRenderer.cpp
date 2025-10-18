#include "OpenGLRenderer.h"
#include "PortalRenderer.h"

OpenGLRenderer::OpenGLRenderer(PortalRenderer* parent):
    QObject(parent)
{}

PortalRenderer* OpenGLRenderer::parent() const
{
    auto ret = qobject_cast<PortalRenderer*>(QObject::parent());
    Q_ASSERT(ret);
    return ret;
}
