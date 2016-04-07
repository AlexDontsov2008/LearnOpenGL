#version 430 core

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

in vec2 TexCoords;

uniform vec3 pointColor;
uniform Material material;

out vec4 color;

void main()
{
    color = vec4(1, 1, 1, 1);
}
