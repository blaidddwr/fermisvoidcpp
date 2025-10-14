#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H
#include <QOpenGLFunctions_4_5_Core>

class OpenGLVertexArray : private QOpenGLFunctions_4_5_Core
{
public:
    OpenGLVertexArray(GLenum mode,GLsizei count,GLsizei instanceCount = 1);
    void addf(
        GLuint location
        ,GLint size
        ,GLenum type
        ,GLsizei stride
        ,int offset
        ,GLuint divisor = 0
        );
    void addi(
        GLuint location
        ,GLint size
        ,GLenum type
        ,GLsizei stride
        ,int offset
        ,GLuint divisor = 0
        );
    void bind();
    void release();
    void draw(GLsizei count = 0);
    void drawInstanced(GLsizei instanceCount = 0,GLsizei count = 0);
private:
    GLuint _id;
    GLenum _mode;
    GLsizei _count;
    GLsizei _instanceCount;
};

#endif
