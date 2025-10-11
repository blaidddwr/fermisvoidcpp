#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H
#include <QOpenGLFunctions_4_5_Core>

class OpenGLShader : private QOpenGLFunctions_4_5_Core
{
public:
    static OpenGLShader fromFile(const QString& path,GLenum type);
    OpenGLShader(const QString& source,GLenum type);
    ~OpenGLShader();
    GLuint id() const;
private:
    GLuint _id;
};

#endif
