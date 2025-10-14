#version 430 core

const float PI = 3.14159265358979323846;

struct Sine
{
    float amplitude;
    float frequency;
    float phase;
    float velocity;
};

in vec2 fPosition;
in flat vec3 fAtomColor;
in flat uvec4 fBonds;

uniform float time;

layout(std430) buffer SineBuffer
{
    uint sineSize;
    Sine sines[];
};

out vec4 color;

float getAngle()
{
    float ret = PI+atan(-fPosition.x,-fPosition.y)+PI/4.0;
    if (ret > (2.0*PI)) ret -= 2.0*PI;
    return ret;
}

float getIntensity(float angle)
{
    float ret = 0.0;
    float retMax = 0.0;
    for (uint i = 0;i < sineSize;i++)
    {
        float theta = (sines[i].frequency*angle)+(sines[i].velocity*time)+sines[i].phase;
        ret += sines[i].amplitude*(1.0-abs(sin(theta)));
        retMax += sines[i].amplitude;
    }
    return ret/retMax;
}

float getRadiusLimit(
    float angle
    ,float atomRadius
    ,float bondRadius
    ,int quadrant
    ,float bondLimitRadius
    ,float intensity
    )
{
    float sine = 0.5*(1.0+sin((4.0*angle)-PI/2.0));
    float ret = bondRadius*sine*intensity;
    if (bool(fBonds[quadrant]&uint(4))) ret = min(bondLimitRadius,ret);
    return atomRadius+ret;
}

int getQuadrant(float angle)
{
    return int(floor(2.0*angle/PI));
}

void main()
{
    //TODO: use framebuffer to render to 1d texture for sine waves, since they vary in only one dimension
    const vec3 colors[3] = vec3[](
        vec3(0.0,0.0,1.0)
        ,vec3(1.0,0.0,0.0)
        ,vec3(1.0,1.0,1.0)
    );
    const vec3 bondColors[4] = vec3[](
        colors[fBonds.x&uint(3)]
        ,colors[fBonds.y&uint(3)]
        ,colors[fBonds.z&uint(3)]
        ,colors[fBonds.w&uint(3)]
    );
    const float atomRadius = 0.3;
    const float bondRadius = 0.7;
    const float bondLimitRadius = 0.2;
    const float atomIntensityRange = 0.3;
    float radius = distance(fPosition,vec2(0.0));
    float angle = getAngle();
    float intensity = getIntensity(angle);
    int q = getQuadrant(angle);
    float radiusLimit = getRadiusLimit(angle,atomRadius,bondRadius,q,bondLimitRadius,intensity);
    float bondNormalRadius = (radius-atomRadius)/(radiusLimit-atomRadius);
    float bondIntensity = sin(PI*bondNormalRadius);
    if (radius > radiusLimit) discard;
    else if (radius < atomRadius)
    {
        color = vec4(cos(PI*radius/atomRadius/2.0)*fAtomColor,1.0);
    }
    else if (radius < radiusLimit)
    {
        color = vec4(bondIntensity*bondColors[q],1.0);
    }
}
