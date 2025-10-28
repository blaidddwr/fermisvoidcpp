#ifndef ATOMRENDERER_H
#define ATOMRENDERER_H
#include "Latch.h"
#include "OpenGLProgram.h"
#include "OpenGLRenderer.h"
#include <QPointF>
class OpenGLBuffer;
class OpenGLVertexArray;

class AtomRenderer : public OpenGLRenderer
{
    Q_OBJECT
public:
    constexpr static int MaxInstanceSize {1024};
    explicit AtomRenderer(PortalRenderer* parent = nullptr);
    virtual ~AtomRenderer() override;
    virtual void initGL() override final;
    virtual void renderGL() override final;
    void setAtoms(const QHash<QPoint,int>& atoms);
    virtual void updateProjection() override final;
    virtual void updateView() override final;
private:
    struct __attribute__((packed)) Color
    {
        void operator=(const QColor& color);
        float r;
        float g;
        float b;
    };
    struct __attribute__((packed)) AtomBuffer
    {
        float x;
        float y;
        Color atomColor;
        quint32 topBond;
        quint32 rightBond;
        quint32 bottomBond;
        quint32 leftBond;
    };
    void initProgram();
    void initVertexArray();
    void updateAtoms();
    constexpr static int SpikeTextureIndex {0};
    AtomBuffer _atomBuffer[MaxInstanceSize];
    Latch<QHash<QPoint,int>> _atoms;
    OpenGLBuffer* _arrayBuffer {nullptr};
    OpenGLBuffer* _instancedBuffer {nullptr};
    OpenGLProgram* _program {nullptr};
    OpenGLProgram::Uniform _atomsCenterUniform;
    OpenGLProgram::Uniform _projectionUniform;
    OpenGLProgram::Uniform _viewUniform;
    OpenGLVertexArray* _vertexArray {nullptr};
    bool _updateProjection {true};
    bool _updateView {true};
};

#endif
