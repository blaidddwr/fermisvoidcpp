#version 430 core

in vec2 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 fPosition;

void main()
{
    vec4 mp = model*vec4(position,1.0,1.0);
    gl_Position = projection*view*mp;
    fPosition = mp.xy;
}
