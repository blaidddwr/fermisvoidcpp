#ifndef WARPRENDERER_H
#define WARPRENDERER_H
#include "Latch.h"
#include "OpenGLProgram.h"
#include "GameRenderer.h"
#include <QColor>
class OpenGLBuffer;
class OpenGLVertexArray;

class WarpRenderer : public GameRenderer
{
    Q_OBJECT
public:
    GAME_RENDERER(WarpRenderer)
    using GameRenderer::GameRenderer;
    virtual ~WarpRenderer() override;
    virtual void renderGL() override final;
    void setColor(const QColor& value);
    void setEVColor(const QColor& value);
    void setRadius(const qreal& value);
protected slots:
    virtual void initGL() override final;
private:
    static constexpr int SmoothTextureIndex {0};
    void initProgram();
    void initVertexArray();
    void updateMVP();
    Latch<QColor> _color;
    Latch<QColor> _evColor;
    Latch<qreal> _radius {0.0};
    OpenGLBuffer* _arrayBuffer {nullptr};
    OpenGLProgram* _program {nullptr};
    OpenGLProgram::Uniform _colorUniform;
    OpenGLProgram::Uniform _evColorUniform;
    OpenGLProgram::Uniform _modelUniform;
    OpenGLProgram::Uniform _projectionUniform;
    OpenGLProgram::Uniform _radiusUniform;
    OpenGLProgram::Uniform _scaleUniform;
    OpenGLProgram::Uniform _viewUniform;
    OpenGLVertexArray* _vertexArray {nullptr};
};

#endif
