#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 3) in vec3 aNormal;

uniform mat4 modelView;
uniform float uTime;
uniform float uWaveAmplitude;
uniform float uWaveFrequency;

out vec3 vFragPos;
out vec3 vNormal;

void main()
{
	vec3 pos = aPos;
	// Desplazamiento sinusoidal en Y para simular corriente
	pos.y += uWaveAmplitude * sin(pos.x * uWaveFrequency + uTime * 2.0)
	       + uWaveAmplitude * 0.5 * cos(pos.z * uWaveFrequency * 0.7 + uTime * 1.5);

	vec4 viewPos = modelView * vec4(pos, 1.0);
	vFragPos = viewPos.xyz;
	vNormal = (modelView * vec4(aNormal, 0.0)).xyz;
	gl_Position = viewPos;
}
