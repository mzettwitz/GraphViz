#version 430 core


in vec3 color;
out vec4 fColor;

void main()
{
    fColor = vec4(color,0.5f);
}