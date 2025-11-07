#include "OpenGLBuffer.h"
#include "OpenGLShader.h"
#include "OpenGLTexture1D.h"
#include "OpenGLVertexArray.h"
#include "PortalRenderer.h"
#include "SinesRenderer.h"
#include "WarpRenderer.h"

WarpRenderer::~WarpRenderer()
{
    delete _vertexArray;
    delete _arrayBuffer;
    delete _program;
}

void WarpRenderer::renderGL()
{
    SinesRenderer::instance().smoothTexture().bind(SmoothTextureIndex);
    _program->use();
    if (
        viewUpdated()
        || projectionUpdated()
    )
    {
        updateMVP();
    }
    if (_color.updated()) _colorUniform.setColor3f(_color.get());
    if (_evColor.updated()) _evColorUniform.setColor3f(_evColor.get());
    if (_radius.updated()) _radiusUniform.set1f(_radius.get());
    if (_scale.updated()) _scaleUniform.set1f(_scale.get());
    _vertexArray->bind();
    _vertexArray->draw();
    _vertexArray->release();
    _program->release();
}

void WarpRenderer::setColor(const QColor& value)
{
    _color = value;
}

void WarpRenderer::setEVColor(const QColor& value)
{
    _evColor = value;
}

void WarpRenderer::setRadius(qreal value)
{
    _radius = value;
}

void WarpRenderer::setScale(qreal value)
{
    _scale = value;
}

void WarpRenderer::initGL()
{
    initializeOpenGLFunctions();
    initProgram();
    initVertexArray();
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
    _colorUniform = _program->uniform("wColor");
    _evColorUniform = _program->uniform("evColor");
    _radiusUniform = _program->uniform("evRadius");
    _scaleUniform = _program->uniform("scale");
    _program->uniform("smoothTexture").set1i(SmoothTextureIndex);
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
    _vertexArray->add(_program->location("position"),2,GL_FLOAT,8,0);
}

void WarpRenderer::updateMVP()
{
    bool success;
    auto model = view().inverted(&success);
    Q_ASSERT(success);
    model.scale(PortalRenderer::instance()->aspectRatio(),1);
    _modelUniform.setMatrix4fv(model);
    _viewUniform.setMatrix4fv(view());
    _projectionUniform.setMatrix4fv(projection());
}
