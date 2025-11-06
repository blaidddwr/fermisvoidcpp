#version 450 core

in vec2 fPosition;

uniform vec3 wColor;

uniform sampler1D bubbleTexture;

out vec4 color;

void main()
{
    float intensity = texture(bubbleTexture,0.5*fPosition.x).r;
    color = vec4(intensity*wColor,1.0);
}
