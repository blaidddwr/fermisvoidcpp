#include "OpenGLBuffer.h"

OpenGLBuffer* OpenGLBuffer::fromData(GLsizeiptr size,const void* data,GLenum usage)
{
    auto ret = new OpenGLBuffer(size,usage);
    ret->write(0,size,data);
    return ret;
}

OpenGLBuffer* OpenGLBuffer::fromData(const QList<float>& vertices,GLenum usage)
{
    auto size = sizeof(float)*vertices.size();
    auto ret = new OpenGLBuffer(size,usage);
    ret->write(0,size,vertices.constData());
    return ret;
}

OpenGLBuffer::OpenGLBuffer(GLsizeiptr size,GLenum usage)
{
    initializeOpenGLFunctions();
    glCreateBuffers(1,&_id);
    glNamedBufferData(_id,size,nullptr,usage);
}

OpenGLBuffer::~OpenGLBuffer()
{
    glDeleteBuffers(1,&_id);
}

void OpenGLBuffer::bind(GLenum target)
{
    glBindBuffer(target,_id);
}

void OpenGLBuffer::bindToShaderStorage(GLuint index)
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,index,_id);
}

void OpenGLBuffer::bindToUniform(GLuint index)
{
    glBindBufferBase(GL_UNIFORM_BUFFER,index,_id);
}

void OpenGLBuffer::read(GLintptr offset, GLsizeiptr size, void* data)
{
    glGetNamedBufferSubData(_id,offset,size,data);
}

void OpenGLBuffer::write(GLintptr offset, GLsizeiptr size, const void* data)
{
    glNamedBufferSubData(_id,offset,size,data);
}
