#version 430 core

in vec2 position;

uniform float x;

out vec2 fPosition;

void main()
{
    gl_Position = vec4(position.x+(2.0*x),position.y,-1.0,1.0);
    fPosition = gl_Position.xy;
}
