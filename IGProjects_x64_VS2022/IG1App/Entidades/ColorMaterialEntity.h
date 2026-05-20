#ifndef _H_CME_H_
#define _H_CME_H_

#include "EntityWithMaterial.h"

// Apartado 58
class ColorMaterialEntity : public EntityWithMaterial
{
public:
	ColorMaterialEntity(Material material);
	void render(const glm::mat4& modelViewMat) const override;

	static void  toggleShowNormals();
private:
	inline static bool mShowNormals = false;
};

#endif //_H_CME_H_

