#ifndef ATOMRENDERER_H
#define ATOMRENDERER_H
#include "Latch.h"
#include "OpenGLProgram.h"
#include "OpenGLRenderer.h"
#include "AtomInstance.h"
class OpenGLBuffer;
class OpenGLVertexArray;

class AtomRenderer : public OpenGLRenderer
{
    Q_OBJECT
public:
    constexpr static int MaxInstanceSize {1024};
    explicit AtomRenderer(PortalRenderer* parent = nullptr);
    virtual ~AtomRenderer() override;
    void initGL();
    void renderGL();
    void setAtoms(const QList<AtomInstance>& atoms);
    void updateProjection();
    void updateView();
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
        float rotation;
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
    constexpr static int SpikeTextureIndex {0};
    AtomBuffer _atomBuffer[MaxInstanceSize];
    Latch<qsizetype> _atomSize;
    OpenGLBuffer* _arrayBuffer {nullptr};
    OpenGLBuffer* _instancedBuffer {nullptr};
    OpenGLProgram* _program {nullptr};
    OpenGLProgram::Uniform _projectionUniform;
    OpenGLProgram::Uniform _viewUniform;
    OpenGLVertexArray* _vertexArray {nullptr};
    bool _updateProjection {true};
    bool _updateView {true};
};

#endif
