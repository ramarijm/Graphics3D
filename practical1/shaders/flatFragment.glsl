#version 400 //GLSL version, fit with OpenGL version

in vec4 fragmentColor;
out vec4 outColor;

void main()
{
    outColor = fragmentColor;
}