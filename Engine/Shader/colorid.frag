#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{    
    color = (texture(image, TexCoords) * vec4(0.0, 0.0, 0.0, 100.0)) + vec4(spriteColor, 0.0);
}