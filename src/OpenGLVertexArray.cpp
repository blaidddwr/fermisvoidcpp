#include "OpenGLVertexArray.h"

OpenGLVertexArray::OpenGLVertexArray(GLenum mode,GLsizei count,GLsizei instanceCount):
    _mode(mode)
    ,_count(count)
    ,_instanceCount(instanceCount)
{
    initializeOpenGLFunctions();
    glGenVertexArrays(1,&_id);
    glBindVertexArray(_id);
}

void OpenGLVertexArray::add(
    GLuint location
    ,GLint size
    ,GLenum type
    ,GLsizei stride
    ,int offset
    ,GLuint divisor
    )
{
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location,size,type,GL_FALSE,stride,reinterpret_cast<const void*>(offset));
    if (divisor)
    {
        glVertexAttribDivisor(location,divisor);
    }
}

void OpenGLVertexArray::bind()
{
    glBindVertexArray(_id);
}

void OpenGLVertexArray::release()
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::draw(GLsizei count)
{
    glDrawArrays(_mode,0,count?count:_count);
}

void OpenGLVertexArray::drawInstanced(GLsizei instanceCount,GLsizei count)
{
    glDrawArraysInstanced(_mode,0,count?count:_count,instanceCount?instanceCount:_instanceCount);
}
