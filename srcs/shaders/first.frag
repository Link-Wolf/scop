#version 330 core
out vec4 FragColor;
uniform float time;
uniform sampler2D textureSampler;
uniform int isTextured;

flat in vec3 ourColor;
in vec2 uv;

void main() 
{
	if (isTextured == 0)
		FragColor = vec4(ourColor, 1.0f);
	else
		FragColor = texture(textureSampler, uv);
}