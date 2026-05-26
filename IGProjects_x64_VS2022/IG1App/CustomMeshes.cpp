#include "IndexMesh.h"

// ===================================================================
// generateBench: Malla indexada manual de un banco rustico
// Requisito 1: Entidad creada mediante malla indexada
// ===================================================================
IndexMesh* IndexMesh::generateBench(GLdouble L)
{
	IndexMesh* mesh = new IndexMesh();
	mesh->mPrimitive = GL_TRIANGLES;

	GLfloat w = (GLfloat)(L);
	GLfloat sH = (GLfloat)(0.08 * L);
	GLfloat sD = (GLfloat)(L * 0.4);
	GLfloat sY = (GLfloat)(L * 0.35);
	GLfloat lW = (GLfloat)(0.08 * L);
	GLfloat bH = (GLfloat)(L * 0.35);
	GLfloat bT = (GLfloat)(0.06 * L);
	GLfloat li = (GLfloat)(0.05 * L);
	GLfloat tW = (GLfloat)(0.05 * L);
	GLfloat tH = (GLfloat)(0.05 * L);

	auto addBox = [&](glm::vec3 minC, glm::vec3 maxC)
		{
			GLuint base = (GLuint)mesh->vVertices.size();
			float x0 = minC.x, y0 = minC.y, z0 = minC.z;
			float x1 = maxC.x, y1 = maxC.y, z1 = maxC.z;

			// +Z
			mesh->vVertices.push_back({ x0, y0, z1 });
			mesh->vVertices.push_back({ x1, y0, z1 });
			mesh->vVertices.push_back({ x1, y1, z1 });
			mesh->vVertices.push_back({ x0, y1, z1 });
			// -Z
			mesh->vVertices.push_back({ x1, y0, z0 });
			mesh->vVertices.push_back({ x0, y0, z0 });
			mesh->vVertices.push_back({ x0, y1, z0 });
			mesh->vVertices.push_back({ x1, y1, z0 });
			// -X
			mesh->vVertices.push_back({ x0, y0, z0 });
			mesh->vVertices.push_back({ x0, y0, z1 });
			mesh->vVertices.push_back({ x0, y1, z1 });
			mesh->vVertices.push_back({ x0, y1, z0 });
			// +X
			mesh->vVertices.push_back({ x1, y0, z1 });
			mesh->vVertices.push_back({ x1, y0, z0 });
			mesh->vVertices.push_back({ x1, y1, z0 });
			mesh->vVertices.push_back({ x1, y1, z1 });
			// +Y
			mesh->vVertices.push_back({ x0, y1, z1 });
			mesh->vVertices.push_back({ x1, y1, z1 });
			mesh->vVertices.push_back({ x1, y1, z0 });
			mesh->vVertices.push_back({ x0, y1, z0 });
			// -Y
			mesh->vVertices.push_back({ x0, y0, z0 });
			mesh->vVertices.push_back({ x1, y0, z0 });
			mesh->vVertices.push_back({ x1, y0, z1 });
			mesh->vVertices.push_back({ x0, y0, z1 });

			for (GLuint i = 0; i < 6; ++i) {
				GLuint b = base + i * 4;
				mesh->vIndexes.push_back(b + 0);
				mesh->vIndexes.push_back(b + 1);
				mesh->vIndexes.push_back(b + 2);
				mesh->vIndexes.push_back(b + 0);
				mesh->vIndexes.push_back(b + 2);
				mesh->vIndexes.push_back(b + 3);
			}
		};

	// Asiento
	addBox({ -w / 2, sY, -sD / 2 },
		{ w / 2, sY + sH, sD / 2 });
	// Respaldo
	addBox({ -w / 2, sY + sH, sD / 2 - bT },
		{ w / 2, sY + sH + bH, sD / 2 });
	// 4 patas
	addBox({ -w / 2 + li, 0, -sD / 2 + li }, { -w / 2 + li + lW, sY, -sD / 2 + li + lW });
	addBox({ w / 2 - li - lW, 0, -sD / 2 + li }, { w / 2 - li, sY, -sD / 2 + li + lW });
	addBox({ -w / 2 + li, 0, sD / 2 - li - lW }, { -w / 2 + li + lW, sY, sD / 2 - li });
	addBox({ w / 2 - li - lW, 0, sD / 2 - li - lW }, { w / 2 - li, sY, sD / 2 - li });
	// 2 travesanos
	addBox({ -w / 2 + li + lW, sY * 0.3f, -sD / 2 + li }, { w / 2 - li - lW, sY * 0.3f + tH, -sD / 2 + li + tW });
	addBox({ -w / 2 + li + lW, sY * 0.3f, sD / 2 - li - tW }, { w / 2 - li - lW, sY * 0.3f + tH, sD / 2 - li });

	mesh->mNumVertices = (GLuint)mesh->vVertices.size();
	mesh->buildNormalVectors();
	return mesh;
}

// ===================================================================
// generateWaterPlane: Plano subdividido para el rio
// ===================================================================
IndexMesh* IndexMesh::generateWaterPlane(GLdouble width, GLdouble depth, GLuint subdivs)
{
	IndexMesh* mesh = new IndexMesh();
	mesh->mPrimitive = GL_TRIANGLES;

	GLuint rows = subdivs;
	GLuint cols = subdivs;
	GLfloat w = (GLfloat)width;
	GLfloat d = (GLfloat)depth;

	for (GLuint r = 0; r <= rows; r++) {
		for (GLuint c = 0; c <= cols; c++) {
			float x = -w / 2.0f + w * (float)c / (float)cols;
			float z = -d / 2.0f + d * (float)r / (float)rows;
			mesh->vVertices.push_back({ x, 0.0f, z });
		}
	}

	for (GLuint r = 0; r < rows; r++) {
		for (GLuint c = 0; c < cols; c++) {
			GLuint tl = r * (cols + 1) + c;
			GLuint tr = tl + 1;
			GLuint bl = (r + 1) * (cols + 1) + c;
			GLuint br = bl + 1;

			mesh->vIndexes.push_back(tl);
			mesh->vIndexes.push_back(bl);
			mesh->vIndexes.push_back(tr);

			mesh->vIndexes.push_back(tr);
			mesh->vIndexes.push_back(bl);
			mesh->vIndexes.push_back(br);
		}
	}

	mesh->mNumVertices = (GLuint)mesh->vVertices.size();
	mesh->buildNormalVectors();
	return mesh;
}