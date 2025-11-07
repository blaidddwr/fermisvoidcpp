#version 450 core

const float PI = 3.14159265358979323846;

in vec2 fPosition;

uniform vec3 wColor;
uniform vec3 evColor;
uniform float evRadius;
uniform float scale;

uniform sampler1D smoothTexture;

out vec4 color;

void main()
{
    const float evBorderRadius = 0.02/scale;
    float radius = distance(fPosition,vec2(0.0));
    if (radius < evRadius) discard;
    float intensity = texture(smoothTexture,0.5*(radius-evRadius)*scale).r;
    if (radius < (evRadius+evBorderRadius))
    {
        float borderNormalRadius = (radius-evRadius)/evBorderRadius;
        vec3 fEVColor = evColor*sin(PI*borderNormalRadius);
        if (borderNormalRadius < 0.5) color = vec4(fEVColor,1.0);
        else color = vec4(max(fEVColor,intensity*wColor),1.0);
    }
    else color = vec4(intensity*wColor,1.0);
}
