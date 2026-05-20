#version 430 core

in vec4 Color;       // normal vector (must be normalized)
out vec4 FragColor;  // fixed-name color variable used by OpenGL

void main()
{
	FragColor = Color;
}
