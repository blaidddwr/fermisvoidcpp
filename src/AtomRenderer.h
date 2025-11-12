#ifndef ATOMRENDERER_H
#define ATOMRENDERER_H
#include "Latch.h"
#include "OpenGLProgram.h"
#include "GameRenderer.h"
#include <QPointF>
class OpenGLBuffer;
class OpenGLVertexArray;

class AtomRenderer : public GameRenderer
{
    Q_OBJECT
public:
    GAME_RENDERER(AtomRenderer)
    constexpr static int MaxInstanceSize {1024};
    using GameRenderer::GameRenderer;
    virtual ~AtomRenderer() override;
    virtual void renderGL() override final;
    void setAtoms(const QHash<QPoint,int>& atoms);
protected slots:
    virtual void initGL() override final;
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
        quint32 bonds[4];
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
};

#endif
