#version 450 core

const float PI = 3.14159265358979323846;

layout (local_size_x=1) in;

struct Sine
{
    vec2 amplitude;
    ivec2 frequency;
    vec2 phase;
    float birthTime;
};

uniform float lifetime;
uniform float time;

layout(std430) buffer SineBuffer
{
    uint sineSize;
    Sine sines[];
};

layout(r32f) uniform image1D smoothTexture;
layout(r32f) uniform image1D bubbleTexture;
layout(r32f) uniform image1D spikeTexture;

void main()
{
    uint self = gl_GlobalInvocationID.x;
    float angle = 2.0*PI*float(self)/float(gl_WorkGroupSize.x*gl_NumWorkGroups.x);
    float smoothIntensity = 0.0;
    float bubbleIntensity = 0.0;
    float spikeIntensity = 0.0;
    float intensityMax = 0.0;
    for (uint i = 0;i < sineSize;i++)
    {
        float age = max(0.0,min(1.0,(time-sines[i].birthTime)/lifetime));
        float theta = (
            (angle*sines[i].frequency.x)
            +sines[i].phase.x
            +(2.0/128.0*PI*time*sines[i].frequency.y)
            +sines[i].phase.y
            );
        float amplitude = sines[i].amplitude.x*sines[i].amplitude.y*sin(PI*age);
        float sineWave = sin(theta);
        smoothIntensity += amplitude*0.5*(1.0+sineWave);
        bubbleIntensity += amplitude*abs(sineWave);
        spikeIntensity += amplitude*(1.0-abs(sineWave));
        intensityMax += amplitude;
    }
    imageStore(smoothTexture,int(self),vec4(smoothIntensity/intensityMax,0.0,0.0,0.0));
    imageStore(bubbleTexture,int(self),vec4(bubbleIntensity/intensityMax,0.0,0.0,0.0));
    imageStore(spikeTexture,int(self),vec4(spikeIntensity/intensityMax,0.0,0.0,0.0));
}
