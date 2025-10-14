#ifndef ATOMRENDERER_H
#define ATOMRENDERER_H
#include "Clock.h"
#include "Latch.h"
#include "OpenGLProgram.h"
#include "OpenGLRenderer.h"
#include "AtomInstance.h"
class OpenGLBuffer;
class OpenGLVertexArray;

class AtomRenderer : public OpenGLRenderer
{
public:
    constexpr static int sineSize {20};
    constexpr static int maxInstanceSize {1024};
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
    struct __attribute__((packed)) Sine
    {
        float amplitude;
        float frequency;
        float phase;
        float velocity;
    };
    struct __attribute__((packed)) SineBuffer
    {
        quint32 size;
        Sine sines[sineSize];
    };
    constexpr static GLuint sineBufferBinding {0};
    void initProgram();
    void initSineBuffer();
    void initVertexArray();
    AtomBuffer _atomBuffer[maxInstanceSize];
    Clock _clock;
    Latch<qsizetype> _atomSize;
    OpenGLBuffer* _arrayBuffer {nullptr};
    OpenGLBuffer* _instancedBuffer {nullptr};
    OpenGLBuffer* _sinesSSBO {nullptr};
    OpenGLProgram* _program {nullptr};
    OpenGLProgram::Uniform _projectionUniform;
    OpenGLProgram::Uniform _timeUniform;
    OpenGLProgram::Uniform _viewUniform;
    OpenGLVertexArray* _vertexArray {nullptr};
    SineBuffer _sineBuffer;
    bool _updateProjection {true};
    bool _updateView {true};
    qreal _time {0.0};
};

#endif
