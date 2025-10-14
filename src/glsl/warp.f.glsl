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
uniform vec4 wColor;
uniform vec4 evColor;
uniform float radius;
uniform float lifeDuration;

layout(std430) buffer SineBuffer
{
    uint sineSize;
    Sine sines[];
};

out vec4 color;

float getLifeScale(uint i)
{
    float age = (lifeDuration-max(sines[i].lifetime-time,0.0))/lifeDuration;
    return sin(PI*age);
}

float getIntensity(uint i,float fRadius)
{
    float angle = 2.0*PI*(
            (sines[i].frequency*fRadius*scale)
            +(sines[i].velocity*time)
        );
    angle += sines[i].phase;
    return 0.5*(1.0+sin(angle));
}

vec3 getEVColor(float fRadius)
{
    const float dropRate = 100.0;
    //TODO: make it smoothly scale off on the inside too
    float angle = min((fRadius-radius)*scale*dropRate,PI/2.0);
    return evColor.rgb*cos(angle);
}

void main()
{
    //TODO: use framebuffer to render to 1d texture for sine waves, since they vary in only one dimension
    float fRadius = distance(fPosition,vec2(0.0));
    if (fRadius < radius)
    {
        discard;
    }
    float intensity = 0.0;
    float intensityMax = 0.0;
    for (uint i = 0;i < sineSize;i++)
    {
        if (time > sines[i].lifetime)
        {
            continue;
        }
        float lifeScale = getLifeScale(i);
        intensity += lifeScale*getIntensity(i,fRadius);
        intensityMax += lifeScale;
    }
    intensity /= intensityMax;
    color = vec4(max(getEVColor(fRadius),wColor.rgb*intensity),1.0);
}
