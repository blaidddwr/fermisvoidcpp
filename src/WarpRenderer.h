#ifndef WARPRENDERER_H
#define WARPRENDERER_H
#include "Clock.h"
#include "Latch.h"
#include "OpenGLProgram.h"
#include "OpenGLRenderer.h"
#include <QColor>
#include <QMatrix4x4>
#include <numbers>
#include <random>
class OpenGLBuffer;
class OpenGLVertexArray;

class WarpRenderer : public OpenGLRenderer
{
public:
    constexpr static int sineSize {20};
    constexpr static qreal sineLifetime {20.0};
    explicit WarpRenderer(PortalRenderer* parent = nullptr);
    virtual ~WarpRenderer() override;
    void initGL();
    void renderGL();
    void setColor(const QColor& value);
    void setEVColor(const QColor& value);
    void setRadius(const qreal& value);
    void updateProjection();
    void updateView();
private:
    struct __attribute__((packed)) Sine
    {
        float amplitude;
        float frequency;
        float phase;
        float velocity;
        float lifetime;
    };
    struct __attribute__((packed)) SineBuffer
    {
        quint32 size;
        Sine sines[sineSize];
    };
    void initProgram();
    void initSineBuffer();
    void initVertexArray();
    void updateMVP();
    void updateNextSine();
    Clock _clock;
    Latch<QColor> _color;
    Latch<QColor> _evColor;
    Latch<qreal> _radius {0.0};
    OpenGLBuffer* _arrayBuffer {nullptr};
    OpenGLBuffer* _sinesSSBO {nullptr};
    OpenGLProgram* _program {nullptr};
    OpenGLProgram::Uniform _colorUniform;
    OpenGLProgram::Uniform _evColorUniform;
    OpenGLProgram::Uniform _modelUniform;
    OpenGLProgram::Uniform _projectionUniform;
    OpenGLProgram::Uniform _radiusUniform;
    OpenGLProgram::Uniform _scaleUniform;
    OpenGLProgram::Uniform _timeUniform;
    OpenGLProgram::Uniform _viewUniform;
    OpenGLVertexArray* _vertexArray {nullptr};
    QMatrix4x4 _model;
    SineBuffer _sineBuffer;
    bool _updateModel {true};
    int _nextSineIndex {0};
    qreal _nextSineTime;
    qreal _time {0.0};
    std::random_device _rd;
    std::mt19937 _gen;
    std::uniform_real_distribution<qreal> _amplitude {1.0,10.0};
    std::uniform_real_distribution<qreal> _frequency {0.1,20.0};
    std::uniform_real_distribution<qreal> _phase {0.0,2.0*std::numbers::pi};
    std::uniform_real_distribution<qreal> _velocity {-0.5,0.5};
};

#endif
