#version 430 core

in vec2 position;
in float rotation;
in vec2 atomOffset;
in vec3 atomColor;
in uvec4 bonds;

uniform mat4 view;
uniform mat4 projection;

out vec2 fPosition;
out flat vec3 fAtomColor;
out flat uvec4 fBonds;

void main()
{
    mat2 rm = mat2(cos(rotation),sin(rotation),-sin(rotation),cos(rotation));
    gl_Position = projection*view*vec4((rm*position)+atomOffset,0.0,1.0);
    fPosition = position;
    fAtomColor = atomColor;
    fBonds = bonds;
}
