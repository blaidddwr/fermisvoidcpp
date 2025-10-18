#ifndef WARPRENDERER_H
#define WARPRENDERER_H
#include "Latch.h"
#include "OpenGLProgram.h"
#include "OpenGLRenderer.h"
#include <QColor>
#include <QMatrix4x4>
class OpenGLBuffer;
class OpenGLVertexArray;

class WarpRenderer : public OpenGLRenderer
{
public:
    explicit WarpRenderer(PortalRenderer* parent = nullptr);
    virtual ~WarpRenderer() override;
    virtual void initGL() override final;
    virtual void renderGL() override final;
    void setColor(const QColor& value);
    void setEVColor(const QColor& value);
    void setRadius(const qreal& value);
    virtual void updateProjection() override final;
    virtual void updateView() override final;
private:
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
    QMatrix4x4 _model;
    bool _updateModel {true};
};

#endif
