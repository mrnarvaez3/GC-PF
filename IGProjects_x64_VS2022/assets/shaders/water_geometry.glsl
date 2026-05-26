#version 430 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

layout (std140, binding = 2) uniform Globals {
	mat4 projection;
};

in vec3 vFragPos[];
in vec3 vNormal[];

out vec3 FragPos;
out vec3 FlatNormal;
noperspective out vec3 Bary;

void main()
{
	// Normal plana: cross de las aristas del triangulo
	vec3 edge1 = vFragPos[1] - vFragPos[0];
	vec3 edge2 = vFragPos[2] - vFragPos[0];
	vec3 flatN = normalize(cross(edge1, edge2));

	// Si la normal apunta en sentido contrario a la camara, invertirla
	vec3 center = (vFragPos[0] + vFragPos[1] + vFragPos[2]) / 3.0;
	if (dot(flatN, normalize(-center)) < 0.0)
		flatN = -flatN;

	FragPos = center;
	FlatNormal = flatN;
	Bary = vec3(1, 0, 0);
	gl_Position = projection * gl_in[0].gl_Position;
	EmitVertex();

	FragPos = center;
	FlatNormal = flatN;
	Bary = vec3(0, 1, 0);
	gl_Position = projection * gl_in[1].gl_Position;
	EmitVertex();

	FragPos = center;
	FlatNormal = flatN;
	Bary = vec3(0, 0, 1);
	gl_Position = projection * gl_in[2].gl_Position;
	EmitVertex();

	EndPrimitive();
}
