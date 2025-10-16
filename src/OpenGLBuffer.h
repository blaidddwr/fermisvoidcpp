#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H
#include <QOpenGLFunctions_4_5_Core>

class OpenGLBuffer : private QOpenGLFunctions_4_5_Core
{
public:
    static OpenGLBuffer* fromData(GLsizeiptr size,const void* data,GLenum usage);
    static OpenGLBuffer* fromData(const QList<float>& vertices,GLenum usage);
    OpenGLBuffer(GLsizeiptr size,GLenum usage);
    ~OpenGLBuffer();
    void bind(GLenum target);
    void bindToShaderStorage(GLuint index);
    void bindToUniform(GLuint index);
    void read(GLintptr offset, GLsizeiptr size, void* data);
    void write(GLintptr offset, GLsizeiptr size, const void* data);
private:
    GLuint _id;
};

#endif
