#ifndef OPENGLTEXTURE1D_H
#define OPENGLTEXTURE1D_H
#include "OpenGLTexture.h"

class OpenGLTexture1D : public OpenGLTexture
{
public:
    OpenGLTexture1D(GLsizei levels,GLenum format,GLsizei width);
};

#endif
