#include "OpenGLBuffer.h"
#include "OpenGLShader.h"
#include "OpenGLVertexArray.h"
#include "PortalRenderer.h"
#include "WarpRenderer.h"
#include <random>

WarpRenderer::WarpRenderer(PortalRenderer* parent):
    OpenGLRenderer(parent)
    ,_gen(_rd())
{}

WarpRenderer::~WarpRenderer()
{
    delete _sinesSSBO;
    delete _vertexArray;
    delete _arrayBuffer;
    delete _program;
}

void WarpRenderer::setColor(const QColor& value)
{
    _color = value;
}

void WarpRenderer::setEVColor(const QColor& value)
{
    _evColor = value;
}

void WarpRenderer::setRadius(const qreal& value)
{
    _radius = value;
}

void WarpRenderer::updateView()
{
    _updateModel = true;
}

void WarpRenderer::updateProjection()
{
    _updateModel = true;
}

void WarpRenderer::initGL()
{
    initializeOpenGLFunctions();
    initProgram();
    initVertexArray();
    initSineBuffer();
    _vertexArray->release();
    _program->release();
}

void WarpRenderer::renderGL()
{
    _time += _clock.mark();
    _program->use();
    if (_nextSineTime < _time) updateNextSine();
    if (_updateModel) updateMVP();
    if (_color.updated()) _colorUniform.setColor4f(_color.get());
    if (_evColor.updated()) _evColorUniform.setColor4f(_evColor.get());
    if (_radius.updated()) _radiusUniform.set1f(_radius.get());
    _timeUniform.set1f(_time);
    _sinesSSBO->bindToShaderStorage(0);
    _vertexArray->bind();
    _vertexArray->draw();
    _vertexArray->release();
    _program->release();
}

void WarpRenderer::initProgram()
{
    auto vertex = OpenGLShader::fromFile(":/glsl/warp.v.glsl",GL_VERTEX_SHADER);
    auto fragment = OpenGLShader::fromFile(":/glsl/warp.f.glsl",GL_FRAGMENT_SHADER);
    _program = new OpenGLProgram({vertex.id(),fragment.id()});
    _modelUniform = _program->uniform("model");
    _viewUniform = _program->uniform("view");
    _projectionUniform = _program->uniform("projection");
    _scaleUniform = _program->uniform("scale");
    _timeUniform = _program->uniform("time");
    _colorUniform = _program->uniform("wColor");
    _evColorUniform = _program->uniform("evColor");
    _radiusUniform = _program->uniform("radius");
    _program->uniform("lifeDuration").set1f(sineLifetime);
    _program->setStorageBlockBinding("SineBuffer",0);
}

void WarpRenderer::initSineBuffer()
{
    _sineBuffer.size = sineSize;
    qreal lf = sineLifetime/qreal(sineSize);
    for (int i = 0;i < sineSize;i++)
    {
        _sineBuffer.sines[i].amplitude = _amplitude(_gen);
        _sineBuffer.sines[i].frequency = _frequency(_gen);
        _sineBuffer.sines[i].phase = _phase(_gen);
        _sineBuffer.sines[i].velocity = _velocity(_gen);
        _sineBuffer.sines[i].lifetime = lf*(qreal(i)+1.0);
    }
    _nextSineTime = lf;
    _sinesSSBO = OpenGLBuffer::fromData(sizeof(SineBuffer),&_sineBuffer,GL_DYNAMIC_DRAW);
}

void WarpRenderer::initVertexArray()
{
    const QList<float> vertices {
        -1.0,-1.0
        ,1.0,-1.0
        ,-1.0,1.0
        ,1.0,1.0
    };
    _arrayBuffer = OpenGLBuffer::fromData(vertices,GL_STATIC_DRAW);
    _arrayBuffer->bind(GL_ARRAY_BUFFER);
    _vertexArray = new OpenGLVertexArray(GL_TRIANGLE_STRIP,vertices.size()/2,1);
    _vertexArray->addf(_program->location("position"),2,GL_FLOAT,8,0);
}

void WarpRenderer::updateMVP()
{
    bool success;
    _model = parent()->view().inverted(&success);
    Q_ASSERT(success);
    _model.scale(parent()->aspectRatio(),1);
    _modelUniform.setMatrix4f(_model);
    _viewUniform.setMatrix4f(parent()->view());
    _projectionUniform.setMatrix4f(parent()->projection());
    _scaleUniform.set1f(parent()->scale());
    _updateModel = false;
}

void WarpRenderer::updateNextSine()
{
    auto& sine = _sineBuffer.sines[_nextSineIndex];
    sine.amplitude = _amplitude(_gen);
    sine.frequency = _frequency(_gen);
    sine.phase = _phase(_gen);
    sine.velocity = _velocity(_gen);
    sine.lifetime = _nextSineTime+sineLifetime;
    _sinesSSBO->write(sizeof(quint32)+(sizeof(Sine)*_nextSineIndex),sizeof(Sine),&sine);
    _nextSineIndex++;
    if (_nextSineIndex >= sineSize) _nextSineIndex = 0;
    _nextSineTime += sineLifetime/qreal(sineSize);
}
