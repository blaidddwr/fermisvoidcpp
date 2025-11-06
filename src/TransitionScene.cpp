#include "TransitionRenderer.h"
#include "TransitionScene.h"

void TransitionScene::setColor(const QColor& value)
{
    if (_color.peek() != value)
    {
        _color = value;
        emit colorChanged(value);
    }
}

void TransitionScene::setX(qreal value)
{
    if (_x.peek() != value)
    {
        _x = value;
        emit xChanged(value);
    }
}

void TransitionScene::activated()
{
    TransitionRenderer::instance().use();
    _color.set();
    _x.set();
}

void TransitionScene::deactivated()
{
    TransitionRenderer::instance().release();
}

void TransitionScene::sync()
{
    auto& transition = TransitionRenderer::instance();
    if (_color.updated()) transition.setColor(_color.get());
    if (_x.updated()) transition.setX(_x.get());
}
