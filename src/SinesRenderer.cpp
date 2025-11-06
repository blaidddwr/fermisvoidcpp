#include "OpenGLBuffer.h"
#include "OpenGLShader.h"
#include "OpenGLTexture1D.h"
#include "SinesRenderer.h"
#include <random>

SinesRenderer::~SinesRenderer()
{
    delete _spikeTexture;
    delete _sinesSSBO;
    delete _program;
}

void SinesRenderer::renderGL()
{
    _time += _clock.mark();
    if (_nextSineTime < _time) updateNextSine();
    _bubbleTexture->bindImage(BubbleTextureIndex,0,GL_WRITE_ONLY);
    _smoothTexture->bindImage(SmoothTextureIndex,0,GL_WRITE_ONLY);
    _spikeTexture->bindImage(SpikeTextureIndex,0,GL_WRITE_ONLY);
    _program->use();
    _timeUniform.set1f(_time);
    _sinesSSBO->bindToShaderStorage(SineBufferIndex);
    glDispatchCompute(TextureWidth,1,1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    _program->release();
}

void SinesRenderer::initGL()
{
    initializeOpenGLFunctions();
    initProgram();
    initSineBuffer();
    initSmoothTexture();
    initBubbleTexture();
    initSpikeTexture();
    _program->release();
}

void SinesRenderer::initBubbleTexture()
{
    _bubbleTexture = new OpenGLTexture1D(1,GL_R32F,TextureWidth);
    _bubbleTexture->setParameter(GL_TEXTURE_WRAP_S,GL_REPEAT);
    _bubbleTexture->setParameter(GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    _bubbleTexture->setParameter(GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

void SinesRenderer::initProgram()
{
    auto compute = OpenGLShader::fromFile(":/glsl/sines.c.glsl",GL_COMPUTE_SHADER);
    _program = new OpenGLProgram({compute.id()});
    _timeUniform = _program->uniform("time");
    _program->setStorageBlockBinding("SineBuffer",SineBufferIndex);
    _program->uniform("lifetime").set1f(SineLifetime);
    _program->uniform("bubbleTexture").set1i(BubbleTextureIndex);
    _program->uniform("smoothTexture").set1i(SmoothTextureIndex);
    _program->uniform("spikeTexture").set1i(SpikeTextureIndex);
}

void SinesRenderer::initSineBuffer()
{
    _sineBuffer.size = SineSize;
    qreal lf = SineLifetime/qreal(SineSize);
    for (int i = 0;i < SineSize;i++)
    {
        for (int j = 0;j < 2;j++)
        {
            _sineBuffer.sines[i].amplitude[j] = _amplitude(_gen);
            _sineBuffer.sines[i].frequency[j] = _frequency(_gen)*(_fPolarity(_gen)?-1:1);
            _sineBuffer.sines[i].phase[j] = _phase(_gen);
        }
        _sineBuffer.sines[i].birthTime = -lf*(qreal(SineSize-i));
    }
    _sinesSSBO = OpenGLBuffer::fromData(sizeof(SineBuffer),&_sineBuffer,GL_STATIC_DRAW);
}

void SinesRenderer::initSmoothTexture()
{
    _smoothTexture = new OpenGLTexture1D(1,GL_R32F,TextureWidth);
    _smoothTexture->setParameter(GL_TEXTURE_WRAP_S,GL_REPEAT);
    _smoothTexture->setParameter(GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    _smoothTexture->setParameter(GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

void SinesRenderer::initSpikeTexture()
{
    _spikeTexture = new OpenGLTexture1D(1,GL_R32F,TextureWidth);
    _spikeTexture->setParameter(GL_TEXTURE_WRAP_S,GL_REPEAT);
    _spikeTexture->setParameter(GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    _spikeTexture->setParameter(GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

void SinesRenderer::updateNextSine()
{
    auto& sine = _sineBuffer.sines[_nextSineIndex];
    for (int j = 0;j < 2;j++)
    {
        sine.amplitude[j] = _amplitude(_gen);
        sine.frequency[j] = _frequency(_gen)*(_fPolarity(_gen)?-1:1);
        sine.phase[j] = _phase(_gen);
    }
    sine.birthTime = _time;
    GLintptr offset = reinterpret_cast<GLintptr>(&sine)-reinterpret_cast<GLintptr>(&_sineBuffer);
    _sinesSSBO->write(offset,sizeof(Sine),&sine);
    _nextSineIndex++;
    if (_nextSineIndex >= SineSize) _nextSineIndex = 0;
    _nextSineTime += SineLifetime/qreal(SineSize);
}
