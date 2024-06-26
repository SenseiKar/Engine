#version 330 core
out vec4 FragColor;

uniform vec4 ourColor;
in vec3 RGColor;
in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture0, TexCoord);
}