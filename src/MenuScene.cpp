#include "MenuScene.h"
#include "WarpRenderer.h"

void MenuScene::setColor(const QColor& value)
{
    if (_color.peek() != value)
    {
        _color = value;
        emit colorChanged(value);
    }
}

void MenuScene::setEVColor(const QColor& value)
{
    if (_evColor.peek() != value)
    {
        _evColor = value;
        emit evColorChanged(value);
    }
}

void MenuScene::setRadius(qreal value)
{
    if (_radius.peek() != value)
    {
        _radius = value;
        emit radiusChanged(value);
    }
}

void MenuScene::activated()
{
    WarpRenderer::instance().use();
    _color.set();
    _evColor.set();
    _radius.set();
}

void MenuScene::deactivated()
{
    WarpRenderer::instance().release();
}

void MenuScene::sync()
{
    auto& warp = WarpRenderer::instance();
    if (_color.updated()) warp.setColor(_color.get());
    if (_evColor.updated()) warp.setEVColor(_evColor.get());
    if (_radius.updated()) warp.setRadius(_radius.get());
}
