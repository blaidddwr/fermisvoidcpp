#include "OpenGLShader.h"
#include <QFile>

OpenGLShader OpenGLShader::fromFile(const QString& path, GLenum type)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed opening shader file:" << path;
        qDebug().noquote() << file.errorString();
        std::exit(-1);
    }
    return OpenGLShader(file.readAll(),type);
}

OpenGLShader::OpenGLShader(const QString& source, GLenum type)
{
    initializeOpenGLFunctions();
    _id = glCreateShader(type);
    auto bytes = source.toUtf8();
    GLint arg4 = bytes.size();
    const GLchar* arg3[1] {bytes.constData()};
    glShaderSource(_id,1,arg3,&arg4);
    glCompileShader(_id);
    GLint param;
    glGetShaderiv(_id,GL_COMPILE_STATUS,&param);
    if (param == GL_FALSE)
    {
        glGetShaderiv(_id,GL_INFO_LOG_LENGTH,&param);
        bytes.resize(param);
        GLsizei length;
        glGetShaderInfoLog(_id,param,&length,bytes.data());
        qDebug() << "Shader Compile Failure:";
        qDebug().noquote() << bytes.constData();
        std::exit(-1);
    }
}

OpenGLShader::~OpenGLShader()
{
    glDeleteShader(_id);
}
