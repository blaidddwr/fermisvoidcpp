#include "OpenGLProgram.h"
#include "OpenGLShader.h"
#include <QColor>
#include <QMatrix4x4>

OpenGLProgram::Uniform::Uniform(OpenGLProgram* program,GLint index):
    _index(index)
    ,_p(program)
{
    Q_ASSERT(program);
}

void OpenGLProgram::Uniform::set1f(float v0)
{
    _p->glUniform1f(_index,v0);
}

void OpenGLProgram::Uniform::set2f(const QPointF& point)
{
    _p->glUniform2f(_index,point.x(),point.y());
}

void OpenGLProgram::Uniform::set1i(int v0)
{
    _p->glUniform1i(_index,v0);
}

void OpenGLProgram::Uniform::set3f(float v0,float v1,float v2)
{
    _p->glUniform3f(_index,v0,v1,v2);
}

void OpenGLProgram::Uniform::setColor3f(const QColor& color)
{
    _p->glUniform3f(_index,color.redF(),color.greenF(),color.blueF());
}

void OpenGLProgram::Uniform::setColor4f(const QColor& color)
{
    _p->glUniform4f(_index,color.redF(),color.greenF(),color.blueF(),color.alphaF());
}

void OpenGLProgram::Uniform::setMatrix4fv(const QMatrix4x4& matrix)
{
    _p->glUniformMatrix4fv(_index,1,GL_FALSE,matrix.constData());
}

OpenGLProgram::OpenGLProgram(const QList<GLuint>& shaders)
{
    initializeOpenGLFunctions();
    _id = glCreateProgram();
    if (!shaders.isEmpty())
    {
        for (auto shader: shaders)
        {
            glAttachShader(_id,shader);
        }
        link();
    }
    use();
}

OpenGLProgram::~OpenGLProgram()
{
    glDeleteProgram(_id);
}

GLint OpenGLProgram::location(const QString& name)
{
    auto ret = glGetAttribLocation(_id,name.toUtf8().constData());
    Q_ASSERT(ret != -1);
    return ret;
}

OpenGLProgram::Uniform OpenGLProgram::uniform(const QString& name)
{
    auto i = glGetUniformLocation(_id,name.toUtf8().constData());
    Q_ASSERT(i != -1);
    return Uniform(this,i);
}

void OpenGLProgram::add(const OpenGLShader& shader)
{
    glAttachShader(_id,shader.id());
}

void OpenGLProgram::link()
{
    glLinkProgram(_id);
    GLint param;
    glGetProgramiv(_id,GL_LINK_STATUS,&param);
    if (param == GL_FALSE)
    {
        glGetProgramiv(_id,GL_INFO_LOG_LENGTH,&param);
        QByteArray bytes(param,Qt::Initialization::Uninitialized);
        GLsizei length;
        glGetProgramInfoLog(_id,param,&length,bytes.data());
        qDebug() << "Program Link Failure:";
        qDebug() << bytes.constData();
        std::exit(-1);
    }
}

void OpenGLProgram::release()
{
    glUseProgram(0);
}

void OpenGLProgram::setStorageBlockBinding(const QString& name, GLuint index)
{
    auto sbIndex = glGetProgramResourceIndex(_id,GL_SHADER_STORAGE_BLOCK,name.toUtf8().constData());
    Q_ASSERT(sbIndex != GL_INVALID_INDEX);
    glShaderStorageBlockBinding(_id,sbIndex,index);
}

void OpenGLProgram::setUniformBlockBinding(const QString& name, GLuint index)
{
    auto ubIndex = glGetUniformBlockIndex(_id,name.toUtf8().constData());
    Q_ASSERT(ubIndex != GL_INVALID_INDEX);
    glUniformBlockBinding(_id,ubIndex,index);
}

void OpenGLProgram::use()
{
    glUseProgram(_id);
}
