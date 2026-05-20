#include "../Entity.h"
#include "../Material.h"

class EntityWithMaterial : public Abs_Entity
{
public:
	EntityWithMaterial();
	void setMaterial(const Material& m);
	void render(const glm::mat4& modelViewMat) const override;
protected:
	Material material;
};

