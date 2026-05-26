#pragma once
#ifndef H_LowPolyEntity_H
#define H_LowPolyEntity_H

#include "../Entity.h"
#include "../Material.h"

class LowPolyEntity : public Abs_Entity
{
public:
	LowPolyEntity(Material material);
	void render(const glm::mat4& modelViewMat) const override;
	void setMaterial(const Material& m) { material = m; }


	static void toggleWireframe() { sWireframe = !sWireframe; }
	static bool wireframeOn() { return sWireframe; }

protected:
	Material material;
	inline static bool sWireframe = true;
	inline static float sWireWidth = 1.2f;
	inline static glm::vec3 sWireColor = { 0.85f, 0.85f, 0.9f };
};

#endif //H_LowPolyEntity_H