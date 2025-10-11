#include "OpenGLRenderer.h"
#include "PortalRenderer.h"

OpenGLRenderer::OpenGLRenderer(PortalRenderer* parent):
    QObject(parent)
    ,_parent(parent)
{
    Q_ASSERT(parent);
}

PortalRenderer* OpenGLRenderer::parent() const
{
    return _parent;
}
