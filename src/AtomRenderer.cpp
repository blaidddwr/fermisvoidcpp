#include "Atom.h"
#include "AtomRenderer.h"
#include "Atoms.h"
#include "OpenGLBuffer.h"
#include "OpenGLShader.h"
#include "OpenGLVertexArray.h"
#include "PortalRenderer.h"
#include <QColor>
#include <random>
#include <QtEndian>

void AtomRenderer::Color::operator=(const QColor& color)
{
    r = color.redF();
    g = color.greenF();
    b = color.blueF();
}

AtomRenderer::AtomRenderer(PortalRenderer* parent):
    OpenGLRenderer(parent)
{}

AtomRenderer::~AtomRenderer()
{
    delete _sinesSSBO;
    delete _vertexArray;
    delete _arrayBuffer;
    delete _instancedBuffer;
    delete _program;
}

void AtomRenderer::initGL()
{
    initializeOpenGLFunctions();
    initProgram();
    initVertexArray();
    initSineBuffer();
    _vertexArray->release();
    _program->release();
}

void AtomRenderer::renderGL()
{
    if (_atomSize.peek())
    {
        _time += _clock.mark();
        _program->use();
        if (_updateView)
        {
            _viewUniform.setMatrix4f(parent()->view());
            _updateView = false;
        }
        if (_updateProjection)
        {
            _projectionUniform.setMatrix4f(parent()->projection());
            _updateProjection = false;
        }
        if (_atomSize.updated())
        {
            auto size = _atomSize.get();
            _instancedBuffer->write(0,sizeof(AtomBuffer)*size,_atomBuffer);
        }
        _timeUniform.set1f(_time);
        _sinesSSBO->bindToShaderStorage(sineBufferBinding);
        _vertexArray->bind();
        _vertexArray->drawInstanced(_atomSize.peek());
        _vertexArray->release();
        _program->release();
    }
}

void AtomRenderer::setAtoms(const QList<AtomInstance>& atoms)
{
    static const quint32 POSITIVE = 0;
    static const quint32 NEGATIVE = 1;
    static const quint32 COVALENT = 2;
    Q_ASSERT(POSITIVE == Atom::Bond::Positive);
    Q_ASSERT(NEGATIVE == Atom::Bond::Negative);
    Q_ASSERT(COVALENT == Atom::Bond::Covalent);
    Q_ASSERT(atoms.size() <= maxInstanceSize);
    _atomSize.set() = atoms.size();
    for (int i = 0;i < atoms.size();i++)
    {
        const auto& ai = atoms[i];
        Q_ASSERT(ai.atomicNumber > 0);
        Q_ASSERT(ai.atomicNumber <= Atoms::instance().size());
        const auto& atom = Atoms::instance().get(ai.atomicNumber);
        auto& atomBuffer = _atomBuffer[i];
        atomBuffer.rotation = ai.rotation;
        atomBuffer.x = ai.x;
        atomBuffer.y = ai.y;
        atomBuffer.atomColor = atom.color();
        atomBuffer.topBond = atom.topBond()+(ai.topBonded?4:0);
        atomBuffer.rightBond = atom.rightBond()+(ai.rightBonded?4:0);
        atomBuffer.bottomBond = atom.bottomBond()+(ai.bottomBonded?4:0);
        atomBuffer.leftBond = atom.leftBond()+(ai.leftBonded?4:0);
    }
}

void AtomRenderer::updateProjection()
{
    _updateProjection = true;
}

void AtomRenderer::updateView()
{
    _updateView = true;
}

void AtomRenderer::initProgram()
{
    auto vertex = OpenGLShader::fromFile(":/glsl/atom.v.glsl",GL_VERTEX_SHADER);
    auto fragment = OpenGLShader::fromFile(":/glsl/atom.f.glsl",GL_FRAGMENT_SHADER);
    _program = new OpenGLProgram({vertex.id(),fragment.id()});
    _viewUniform = _program->uniform("view");
    _projectionUniform = _program->uniform("projection");
    _timeUniform = _program->uniform("time");
    _program->setStorageBlockBinding("SineBuffer",sineBufferBinding);
}

void AtomRenderer::initSineBuffer()
{
    _sineBuffer.size = sineSize;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<qreal> amplitude {1.0,10.0};
    std::uniform_real_distribution<qreal> frequency {10.0,50.0};
    std::uniform_real_distribution<qreal> phase {0.0,2.0*std::numbers::pi};
    std::uniform_real_distribution<qreal> velocity {-2.0,2.0};
    for (int i = 0;i < sineSize;i++)
    {
        _sineBuffer.sines[i].amplitude = amplitude(gen);
        _sineBuffer.sines[i].frequency = frequency(gen);
        _sineBuffer.sines[i].phase = phase(gen);
        _sineBuffer.sines[i].velocity = velocity(gen);
    }
    _sinesSSBO = OpenGLBuffer::fromData(sizeof(SineBuffer),&_sineBuffer,GL_STATIC_DRAW);
}

void AtomRenderer::initVertexArray()
{
    const QList<float> vertices {
        -1.0,-1.0
        ,1.0,-1.0
        ,-1.0,1.0
        ,1.0,1.0
    };
    _arrayBuffer = OpenGLBuffer::fromData(vertices,GL_STATIC_DRAW);
    _arrayBuffer->bind(GL_ARRAY_BUFFER);
    _vertexArray = new OpenGLVertexArray(GL_TRIANGLE_STRIP,vertices.size()/2,maxInstanceSize);
    _vertexArray->addf(_program->location("position"),2,GL_FLOAT,8,0);
    _instancedBuffer = new OpenGLBuffer(sizeof(AtomBuffer)*maxInstanceSize,GL_DYNAMIC_DRAW);
    _instancedBuffer->bind(GL_ARRAY_BUFFER);
    _vertexArray->addf(_program->location("rotation"),1,GL_FLOAT,40,0,1);
    _vertexArray->addf(_program->location("atomOffset"),2,GL_FLOAT,40,4,1);
    _vertexArray->addf(_program->location("atomColor"),3,GL_FLOAT,40,12,1);
    _vertexArray->addi(_program->location("bonds"),4,GL_UNSIGNED_INT,40,24,1);
}
