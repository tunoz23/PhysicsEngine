#version 410 core

layout(location = 0) in vec3 inPos;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	gl_Position = projection * model * vec4(inPos, 1.0);
}