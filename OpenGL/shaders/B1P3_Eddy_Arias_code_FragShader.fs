#version 330 core
out vec4 FragColor;

in vec3 ourColor;
uniform float r1;
uniform float g1;
uniform float b1;

void main()
{
    FragColor = vec4(ourColor.x+r1,ourColor.y+g1,ourColor.z+b1, 1.0f);
}