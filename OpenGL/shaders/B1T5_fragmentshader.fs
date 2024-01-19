#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

out vec4 finalColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float visibleColor;

void main()
{
        finalColor = mix(texture(texture2, TexCoord),vec4(ourColor, 1.0) ,visibleColor);
}