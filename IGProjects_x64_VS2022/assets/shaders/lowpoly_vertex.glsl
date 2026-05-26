#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 3) in vec3 aNormal;

uniform mat4 modelView;

// Pasamos al geometry shader en espacio de vista
out vec3 vFragPos;
out vec3 vNormal;

void main()
{
	vec4 viewPos = modelView * vec4(aPos, 1.0);
	vFragPos = viewPos.xyz;
	vNormal = (modelView * vec4(aNormal, 0.0)).xyz;
	gl_Position = viewPos; // projection se aplica en geometry
}
