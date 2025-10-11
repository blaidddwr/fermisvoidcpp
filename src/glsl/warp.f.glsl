#version 430 core

const float PI = 3.14159265358979323846;

struct Sine
{
    float amplitude;
    float frequency;
    float phase;
    float velocity;
    float lifetime;
};

in vec2 fPosition;

uniform float scale;
uniform float time;
uniform vec4 warpColor;
uniform vec4 evColor;
uniform float radius;
uniform float lifeDuration;

layout(std430) buffer SineBuffer
{
    uint sineSize;
    Sine sines[];
};

out vec4 color;

void main()
{
    float d = distance(fPosition,vec2(0.0));
    if (d < radius)
    {
        discard;
    }
    float f = 0.0;
    float den = 0.0;
    for (uint i = 0;i < sineSize;i++)
    {
        if (time > sines[i].lifetime)
        {
            continue;
        }
        float a = sin(PI*(lifeDuration-max(sines[i].lifetime-time,0.0))/lifeDuration);
        f += a*0.5*(1.0+sin(2.0*PI*((sines[i].frequency*d*scale)+(sines[i].velocity*time))+sines[i].phase));
        den += a;
    }
    f /= den;
    vec3 ev = evColor.rgb*cos(min((d-radius)*scale*100.0,PI/2.0));
    color = vec4(max(ev,warpColor.rgb*f),1.0);
}
