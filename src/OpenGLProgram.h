#ifndef OPENGLPROGRAM_H
#define OPENGLPROGRAM_H
#include <QOpenGLFunctions_4_5_Core>
class OpenGLShader;

class OpenGLProgram : private QOpenGLFunctions_4_5_Core
{
public:
    class Uniform
    {
    public:
        Uniform() = default;
        Uniform(OpenGLProgram* program,GLint index);
        void set1f(float v0);
        void set1i(int v0);
        void set3f(float v0,float v1,float v2);
        void setColor3f(const QColor& color);
        void setColor4f(const QColor& color);
        void setMatrix4fv(const QMatrix4x4& matrix);
    private:
        GLint _index {-1};
        OpenGLProgram* _p {nullptr};
    };
    OpenGLProgram(const QList<GLuint>& shaders = {});
    ~OpenGLProgram();
    GLint location(const QString& name);
    Uniform uniform(const QString& name);
    void add(const OpenGLShader& shader);
    void link();
    void release();
    void setStorageBlockBinding(const QString& name, GLuint index);
    void setUniformBlockBinding(const QString& name, GLuint index);
    void use();
private:
    GLuint _id;
};

#endif
