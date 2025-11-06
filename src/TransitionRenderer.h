#ifndef TRANSITIONRENDERER_H
#define TRANSITIONRENDERER_H
#include "GameRenderer.h"
#include "Latch.h"
#include "OpenGLProgram.h"
#include <QColor>
class OpenGLBuffer;
class OpenGLVertexArray;

class TransitionRenderer : public GameRenderer
{
    Q_OBJECT
public:
    GAME_RENDERER(TransitionRenderer)
    using GameRenderer::GameRenderer;
    virtual ~TransitionRenderer() override;
    virtual void renderGL() override final;
    void setColor(const QColor& value);
    void setX(const qreal& value);
protected slots:
    virtual void initGL() override final;
private:
    static constexpr int BubbleTextureIndex {0};
    void initProgram();
    void initVertexArray();
    Latch<QColor> _color;
    Latch<qreal> _x {0.0};
    OpenGLBuffer* _arrayBuffer {nullptr};
    OpenGLProgram* _program {nullptr};
    OpenGLProgram::Uniform _colorUniform;
    OpenGLProgram::Uniform _xUniform;
    OpenGLVertexArray* _vertexArray {nullptr};
};

#endif
