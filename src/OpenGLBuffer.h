#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H
#include <QOpenGLFunctions_4_5_Core>

class OpenGLBuffer : private QOpenGLFunctions_4_5_Core
{
public:
    static OpenGLBuffer* fromData(const QList<float>& vertices,GLenum usage);
    static OpenGLBuffer* fromData(GLsizeiptr size,const void* data,GLenum usage);
    OpenGLBuffer(GLsizeiptr size,GLenum usage);
    ~OpenGLBuffer();
    void write(GLintptr offset, GLsizeiptr size, const void* data);
    void read(GLintptr offset, GLsizeiptr size, void* data);
    void bind(GLenum target);
    void bindToUniform(GLuint index);
    void bindToShaderStorage(GLuint index);
private:
    GLuint _id;
};

#endif
