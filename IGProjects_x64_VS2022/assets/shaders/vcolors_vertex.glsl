#version 430 core

layout (location = 0) in vec3 aPos;  // input vertex in local coordinates
layout (location = 1) in vec4 aColor;  // input vertex in local coordinates

uniform mat4 modelView;  // model-view matrix

layout (std140, binding = 2) uniform Globals {
	mat4 projection;  // projection matrix
};

out vec4 vertexColor;

void main()
{
	gl_Position = projection * modelView * vec4(aPos, 1.0);
	vertexColor = aColor;
}
