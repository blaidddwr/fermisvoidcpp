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
    switch (type)
    {
    case GL_FLOAT:
        glVertexAttribPointer(
            location
            ,size
            ,type
            ,GL_FALSE
            ,stride
            ,reinterpret_cast<const void*>(offset)
            );
        break;
    case GL_UNSIGNED_INT:
        glVertexAttribIPointer(location,size,type,stride,reinterpret_cast<const void*>(offset));
        break;
    default:
        Q_ASSERT(false);
    }
    if (divisor)
    {
        glVertexAttribDivisor(location,divisor);
    }
}

void OpenGLVertexArray::bind()
{
    glBindVertexArray(_id);
}

void OpenGLVertexArray::draw(GLsizei count)
{
    glDrawArrays(_mode,0,count?count:_count);
}

void OpenGLVertexArray::drawInstanced(GLsizei instanceCount,GLsizei count)
{
    glDrawArraysInstanced(_mode,0,count?count:_count,instanceCount?instanceCount:_instanceCount);
}

void OpenGLVertexArray::release()
{
    glBindVertexArray(0);
}
