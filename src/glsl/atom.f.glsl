#version 450 core

const float PI = 3.14159265358979323846;
const float atomRadius = 0.1;
const float atomFadeRadius = 0.2;
const float bondLimitRadius = 0.51;
const float bondMaxRadius = 1.0;

in vec2 fPosition;
in flat vec3 fAtomColor;
in flat uvec4 fBonds;

uniform sampler1D spikeTexture;

out vec4 color;

float getNormalAngle()
{
    float ret = PI+atan(-fPosition.x,-fPosition.y)+PI/4.0;
    if (ret > (2.0*PI)) ret -= 2.0*PI;
    return ret/(2.0*PI);
}

float getBondRadius(uint q,float intensity)
{
    float ret = (bondMaxRadius-atomFadeRadius)*intensity;
    if (bool(fBonds[q]&uint(4))) ret = min(bondLimitRadius-atomFadeRadius,ret);
    return atomFadeRadius+ret;
}

void main()
{
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
    float radius = distance(fPosition,vec2(0.0));
    float angle = getNormalAngle();
    uint q = uint(floor(4.0*angle));
    float intensity = texture(spikeTexture,angle).r;
    float bondRadius = getBondRadius(q,intensity);
    if (radius < atomRadius) color = vec4(fAtomColor,1.0);
    else if (radius < atomFadeRadius)
    {
        float normalFadeRadius = (atomFadeRadius-radius)/(atomFadeRadius-atomRadius);
        color = vec4(sin(PI*normalFadeRadius/2.0)*fAtomColor,1.0);
    }
    else if (radius < bondRadius)
    {
        float bondNormalRadius = (radius-atomFadeRadius)/(bondRadius-atomFadeRadius);
        float bondIntensity = sin(PI*bondNormalRadius);
        vec3 bondColor = (
            bondColors[0]*sin(4.0*PI*min(angle,0.25))
            +bondColors[1]*sin(4.0*PI*min(max(angle-0.25,0.0),0.25))
            +bondColors[2]*sin(4.0*PI*min(max(angle-0.5,0.0),0.25))
            +bondColors[3]*sin(4.0*PI*min(max(angle-0.75,0.0),0.25))
            );
        color = vec4(bondIntensity*bondColor,1.0);
    }
    else discard;
}
