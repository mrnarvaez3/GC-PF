#ifndef H_SceneFinal_H
#define H_SceneFinal_H

#include "../Scene.h"

class WaterMill;
class Lantern;
class WaterEntity;

class SceneFinal : public Scene
{
public:
	void init() override;
	void render(Camera const& cam) const override;
	void load() override;
	void unload() override;
	void update() override;
	bool handleEvents(unsigned int key) override;

private:
	WaterMill* mWaterMill = nullptr;
	Lantern* mLantern = nullptr;
	WaterEntity* mRiver = nullptr;
	DirLight* mMoonLight = nullptr;
};

#endif //H_SceneFinal_H