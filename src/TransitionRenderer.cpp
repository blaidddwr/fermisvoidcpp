#include "OpenGLBuffer.h"
#include "OpenGLShader.h"
#include "OpenGLTexture1D.h"
#include "OpenGLVertexArray.h"
#include "SinesRenderer.h"
#include "TransitionRenderer.h"

TransitionRenderer::~TransitionRenderer()
{
    delete _vertexArray;
    delete _arrayBuffer;
    delete _program;
}

void TransitionRenderer::renderGL()
{
    SinesRenderer::instance().bubbleTexture().bind(BubbleTextureIndex);
    _program->use();
    if (_color.updated()) _colorUniform.setColor3f(_color.get());
    if (_x.updated()) _xUniform.set1f(_x.get());
    _vertexArray->bind();
    _vertexArray->draw();
    _vertexArray->release();
    _program->release();
}

void TransitionRenderer::setColor(const QColor& value)
{
    _color = value;
}

void TransitionRenderer::setX(const qreal& value)
{
    _x = value;
}

void TransitionRenderer::initGL()
{
    initializeOpenGLFunctions();
    initProgram();
    initVertexArray();
    _vertexArray->release();
    _program->release();
}

void TransitionRenderer::initProgram()
{
    auto vertex = OpenGLShader::fromFile(":/glsl/transition.v.glsl",GL_VERTEX_SHADER);
    auto fragment = OpenGLShader::fromFile(":/glsl/transition.f.glsl",GL_FRAGMENT_SHADER);
    _program = new OpenGLProgram({vertex.id(),fragment.id()});
    _colorUniform = _program->uniform("wColor");
    _xUniform = _program->uniform("x");
    _program->uniform("bubbleTexture").set1i(BubbleTextureIndex);
}

void TransitionRenderer::initVertexArray()
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
