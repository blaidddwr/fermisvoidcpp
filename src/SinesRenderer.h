#ifndef SINESRENDERER_H
#define SINESRENDERER_H
#include "Clock.h"
#include "OpenGLProgram.h"
#include "OpenGLRenderer.h"
#include <numbers>
#include <random>
class OpenGLBuffer;
class OpenGLTexture1D;

class SinesRenderer : public OpenGLRenderer
{
    Q_OBJECT
public:
    constexpr static int SineSize {32};
    constexpr static int TextureWidth {512};
    constexpr static qreal SineLifetime {32.0};
    SinesRenderer(PortalRenderer* parent = nullptr);
    virtual ~SinesRenderer();
    OpenGLTexture1D& bubbleTexture() const { return *_bubbleTexture; }
    OpenGLTexture1D& smoothTexture() const { return *_smoothTexture; }
    OpenGLTexture1D& spikeTexture() const { return *_spikeTexture; }
    virtual void initGL() override final;
    virtual void renderGL() override final;
private:
    struct __attribute__((packed)) Sine
    {
        float amplitude[2];
        qint32 frequency[2];
        float phase[2];
        float birthTime;
        char p0[4];
    };
    struct __attribute__((packed)) SineBuffer
    {
        quint32 size;
        char p0[4];
        Sine sines[SineSize];
    };
    void initBubbleTexture();
    void initProgram();
    void initSineBuffer();
    void initSmoothTexture();
    void initSpikeTexture();
    void updateNextSine();
    static const GLuint BubbleTextureIndex {0};
    static const GLuint SineBufferIndex {0};
    static const GLuint SmoothTextureIndex {1};
    static const GLuint SpikeTextureIndex {2};
    Clock _clock;
    OpenGLBuffer* _sinesSSBO {nullptr};
    OpenGLProgram* _program {nullptr};
    OpenGLProgram::Uniform _timeUniform;
    OpenGLTexture1D* _bubbleTexture {nullptr};
    OpenGLTexture1D* _smoothTexture {nullptr};
    OpenGLTexture1D* _spikeTexture {nullptr};
    SineBuffer _sineBuffer;
    int _nextSineIndex {0};
    qreal _nextSineTime {0.0};
    qreal _time {0.0};
    std::bernoulli_distribution _fPolarity {0.5};
    std::random_device _rd;
    std::mt19937 _gen;
    std::uniform_int_distribution<> _frequency {1,int(floor(qreal(TextureWidth)/10.0))};
    std::uniform_real_distribution<qreal> _amplitude {0.1,1.0};
    std::uniform_real_distribution<qreal> _phase {0.0,2.0*std::numbers::pi};
};

#endif
