#include "OpenGLTexture.h"

OpenGLTexture::OpenGLTexture(GLenum target,GLenum format):
    _format(format)
    ,_target(target)
{
    initializeOpenGLFunctions();
    glCreateTextures(target,1,&_id);
}

OpenGLTexture::~OpenGLTexture()
{
    glDeleteTextures(1,&_id);
}

void OpenGLTexture::bind(GLenum index)
{
    glActiveTexture(GL_TEXTURE0+index);
    glBindTexture(_target,_id);
}

void OpenGLTexture::bindImage(GLenum index,GLint level,GLenum access)
{
    glBindImageTexture(index,_id,level,GL_FALSE,0,access,_format);
}

void OpenGLTexture::generateMipMaps()
{
    glGenerateTextureMipmap(_id);
}

void OpenGLTexture::setParameter(GLenum name,GLint value)
{
    glTextureParameteri(_id,name,value);
}
