#include "OpenGLTexture1D.h"

OpenGLTexture1D::OpenGLTexture1D(GLsizei levels,GLenum format,GLsizei width):
    OpenGLTexture(GL_TEXTURE_1D,format)
{
    glTextureStorage1D(id(),levels,format,width);
}
