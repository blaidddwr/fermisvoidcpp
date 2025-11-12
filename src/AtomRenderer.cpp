#include "Atom.h"
#include "AtomRenderer.h"
#include "Atoms.h"
#include "Molecule.h"
#include "OpenGLBuffer.h"
#include "OpenGLShader.h"
#include "OpenGLTexture1D.h"
#include "OpenGLVertexArray.h"
#include "SinesRenderer.h"
#include "WarpRenderer.h"
#include <QColor>

AtomRenderer::~AtomRenderer()
{
    delete _vertexArray;
    delete _arrayBuffer;
    delete _instancedBuffer;
    delete _program;
}

void AtomRenderer::renderGL()
{
    if (!_atoms.peek().isEmpty())
    {
        SinesRenderer::instance().spikeTexture().bind(SpikeTextureIndex);
        _program->use();
        if (viewUpdated()) _viewUniform.setMatrix4fv(view());
        if (projectionUpdated()) _projectionUniform.setMatrix4fv(projection());
        if (_atoms.updated()) updateAtoms();
        _vertexArray->bind();
        _vertexArray->drawInstanced(_atoms.peek().size());
        _vertexArray->release();
        _program->release();
    }
}

void AtomRenderer::setAtoms(const QHash<QPoint,int>& atoms)
{
    _atoms.set() = atoms;
}

void AtomRenderer::initGL()
{
    initializeOpenGLFunctions();
    initProgram();
    initVertexArray();
    _vertexArray->release();
    _program->release();
}

void AtomRenderer::Color::operator=(const QColor& color)
{
    r = color.redF();
    g = color.greenF();
    b = color.blueF();
}

void AtomRenderer::initProgram()
{
    auto vertex = OpenGLShader::fromFile(":/glsl/atom.v.glsl",GL_VERTEX_SHADER);
    auto fragment = OpenGLShader::fromFile(":/glsl/atom.f.glsl",GL_FRAGMENT_SHADER);
    _program = new OpenGLProgram({vertex.id(),fragment.id()});
    _viewUniform = _program->uniform("view");
    _projectionUniform = _program->uniform("projection");
    _program->uniform("spikeTexture").set1i(SpikeTextureIndex);
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
    _vertexArray = new OpenGLVertexArray(GL_TRIANGLE_STRIP,vertices.size()/2,MaxInstanceSize);
    _vertexArray->add(_program->location("position"),2,GL_FLOAT,8,0);
    _instancedBuffer = new OpenGLBuffer(sizeof(AtomBuffer)*MaxInstanceSize,GL_DYNAMIC_DRAW);
    _instancedBuffer->bind(GL_ARRAY_BUFFER);
    _vertexArray->add(_program->location("atomOffset"),2,GL_FLOAT,36,0,1);
    _vertexArray->add(_program->location("atomColor"),3,GL_FLOAT,36,8,1);
    _vertexArray->add(_program->location("bonds"),4,GL_UNSIGNED_INT,36,20,1);
}

void AtomRenderer::updateAtoms()
{
    const auto& atoms = _atoms.get();
    Q_ASSERT(atoms.size() <= MaxInstanceSize);
    static const quint32 POSITIVE = 0;
    static const quint32 NEGATIVE = 1;
    static const quint32 COVALENT = 2;
    Q_ASSERT(POSITIVE == static_cast<int>(Atom::Bond::Positive));
    Q_ASSERT(NEGATIVE == static_cast<int>(Atom::Bond::Negative));
    Q_ASSERT(COVALENT == static_cast<int>(Atom::Bond::Covalent));
    Q_ASSERT(atoms.size() <= MaxInstanceSize);
    int c = 0;
    for (auto i = atoms.begin();i != atoms.end();i++)
    {
        auto x = i.key().x();
        auto y = i.key().y();
        auto an = i.value();
        Q_ASSERT(an > 0);
        Q_ASSERT(an <= Atoms::instance().size());
        const auto& atom = Atoms::instance().get(an);
        auto& atomBuffer = _atomBuffer[c];
        atomBuffer.x = x;
        atomBuffer.y = y;
        atomBuffer.atomColor = atom.color();
        for (int i = 0;i < 4;i++)
        {
            atomBuffer.bonds[i] = static_cast<int>(atom.bond(Atom::direction(i)));
            if (atoms.contains(Molecule::neighbor({x,y},i))) atomBuffer.bonds[i] += 4;
        }
        c++;
    }
    _instancedBuffer->write(0,sizeof(AtomBuffer)*atoms.size(),_atomBuffer);
}
