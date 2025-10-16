#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H
#include <QOpenGLFunctions_4_5_Core>

class OpenGLTexture : public QOpenGLFunctions_4_5_Core
{
public:
    OpenGLTexture(GLenum target,GLenum format);
    ~OpenGLTexture();
    void bind(GLenum index);
    void bindImage(GLenum index,GLint level,GLenum access);
    void generateMipMaps();
    void setParameter(GLenum name,GLint value);
protected:
    GLenum format() const { return _format; }
    GLuint id() const { return _id; }
private:
    GLenum _format;
    GLenum _target;
    GLuint _id;
};

#endif
