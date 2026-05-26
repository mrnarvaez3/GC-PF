#include "SceneFinal.h"

#include "../Material.h"
#include "../Entidades/LowPolyEntity.h"
#include "../Entidades/LowPolyCone.h"
#include "../Entidades/Mountain.h"
#include "../Entidades/Lake.h"
#include "../Entidades/LowPolySphere.h"
#include "../Entidades/LowPolyDisk.h"
#include "../Entidades/LowPolyBox.h"
#include "../Entidades/Bench.h"
#include "../Entidades/Barrel.h"
#include "../Entidades/WaterMill.h"
#include "../Entidades/Lantern.h"
#include "../Entidades/WaterEntity.h"
#include "../Entidades/Skybox.h"
#include "../Entidades/IndexedBox.h"

#include <glm/gtc/matrix_transform.hpp>

void SceneFinal::init()
{
	Scene::init();
	dLight->setEnabled(false);

	// ============================================================
	// Luz de luna - intensa para que se vea bien
	// ============================================================
	mMoonLight = new DirLight(1);
	mMoonLight->setAmb({ 0.2f, 0.2f, 0.35f });
	mMoonLight->setDiff({ 0.2f, 0.2f, 0.9f });
	mMoonLight->setSpec({ 0.25f, 0.25f, 0.4f });
	mMoonLight->setDirection(glm::vec3(-0.5f, -1.0f, -0.3f));
	gLights.push_back(mMoonLight);

	GLfloat L = 120.0f;
	GLfloat casaX = 80.0f;
	GLfloat casaZ = 0.0f;

	// ============================================================
	// Farol con luz calida
	// ============================================================
	mLantern = new Lantern(50.0);
	mLantern->setModelMat(glm::translate(glm::mat4(1.0f),
		glm::vec3(casaX + 20, 55, casaZ + L / 2 + 2)));
	gObjects.push_back(mLantern);


	// ============================================================
	// Materiales con ambient alto para escena nocturna visible
	// ============================================================
	Material stoneMat(glm::vec3(0.6f, 0.58f, 0.55f));
	stoneMat.setAmb({ 0.3f, 0.29f, 0.27f });
	stoneMat.setDiff({ 0.6f, 0.58f, 0.55f });
	stoneMat.setSpec({ 0.1f, 0.1f, 0.1f });
	stoneMat.setExp(4.0f);

	Material woodMat(glm::vec3(0.55f, 0.35f, 0.18f));
	woodMat.setAmb({ 0.28f, 0.18f, 0.09f });
	woodMat.setDiff({ 0.55f, 0.35f, 0.18f });
	woodMat.setSpec({ 0.06f, 0.05f, 0.03f });
	woodMat.setExp(4.0f);

	Material roofMat(glm::vec3(0.42f, 0.44f, 0.58f));
	roofMat.setAmb({ 0.22f, 0.23f, 0.3f });
	roofMat.setDiff({ 0.42f, 0.44f, 0.58f });
	roofMat.setSpec({ 0.08f, 0.08f, 0.1f });
	roofMat.setExp(4.0f);

	// Suelo:
	Material groundMat(glm::vec3(0.15f, 0.28f, 0.1f));
	groundMat.setAmb({ 0.08f, 0.14f, 0.05f });
	groundMat.setDiff({ 0.15f, 0.28f, 0.1f });
	groundMat.setSpec({ 0.01f, 0.01f, 0.01f });
	groundMat.setExp(2.0f);

	Material waterMat(glm::vec3(0.2f, 0.38f, 0.7f));
	waterMat.setAmb({ 0.12f, 0.2f, 0.4f });
	waterMat.setDiff({ 0.2f, 0.38f, 0.7f });
	waterMat.setSpec({ 0.4f, 0.45f, 0.55f });
	waterMat.setExp(32.0f);

	Material rockMat(glm::vec3(0.5f, 0.5f, 0.52f));
	rockMat.setAmb({ 0.25f, 0.25f, 0.26f });
	rockMat.setDiff({ 0.5f, 0.5f, 0.52f });
	rockMat.setSpec({ 0.06f, 0.06f, 0.07f });
	rockMat.setExp(4.0f);

	Material clayMat(glm::vec3(0.7f, 0.42f, 0.25f));
	clayMat.setAmb({ 0.35f, 0.21f, 0.12f });
	clayMat.setDiff({ 0.7f, 0.42f, 0.25f });
	clayMat.setSpec({ 0.1f, 0.08f, 0.05f });
	clayMat.setExp(8.0f);

	Material mountainMat(glm::vec3(0.2f, 0.25f, 0.32f));
	mountainMat.setAmb({ 0.12f, 0.14f, 0.18f });
	mountainMat.setDiff({ 0.2f, 0.25f, 0.32f });
	mountainMat.setSpec({ 0.03f, 0.03f, 0.03f });
	mountainMat.setExp(2.0f);

	Material benchMat(glm::vec3(0.5f, 0.32f, 0.16f));
	benchMat.setAmb({ 0.25f, 0.16f, 0.08f });
	benchMat.setDiff({ 0.5f, 0.32f, 0.16f });
	benchMat.setSpec({ 0.08f, 0.06f, 0.03f });
	benchMat.setExp(6.0f);

	// ============================================================
	// Skybox nocturno estrellado
	// ============================================================
	Skybox* skybox = new Skybox(3500.0, texManager->getTexture("noche2.jpg"), false);
	gObjects.push_back(skybox);

	// ============================================================
	// Suelo:
	// ============================================================
	IndexedBox* suelo = new IndexedBox(1, groundMat);
	suelo->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5f, 0))
		* glm::scale(glm::mat4(1.0f), glm::vec3(3500.0f, 1.0f, 3500.0f)));
	gObjects.push_back(suelo);

	// ============================================================
	// CASA:
	// ============================================================

	LowPolyBox* casaCuerpo = new LowPolyBox(L, stoneMat);
	casaCuerpo->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(casaX, L / 2, casaZ)));
	gObjects.push_back(casaCuerpo);

	// Techo encima de la casa
	LowPolyCone* techo = new LowPolyCone(50, L * 0.88f, 0, 4, 4, roofMat);
	techo->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(casaX, L, casaZ))
		* glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0, 1, 0)));
	gObjects.push_back(techo);

	// Puerta
	LowPolyBox* puerta = new LowPolyBox(1, woodMat);
	puerta->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(casaX, 25, casaZ + L / 2 + 1))
		* glm::scale(glm::mat4(1.0f), glm::vec3(28.0f, 55.0f, 2.0f)));
	gObjects.push_back(puerta);

	// ============================================================
	// NORIA
	// ============================================================
	GLfloat noriaR = 55.0f;
	GLfloat noriaX = casaX - L / 2 - noriaR * 0.4f;

	mWaterMill = new WaterMill(noriaR);
	glm::mat4 noriaMat = glm::translate(glm::mat4(1.0f),
		glm::vec3(noriaX, noriaR, casaZ));
	noriaMat = glm::rotate(noriaMat, glm::radians(90.0f), glm::vec3(0, 1, 0));
	mWaterMill->setModelMat(noriaMat);
	gObjects.push_back(mWaterMill);

	// Soporte noria: brazo horizontal desde la pared al centro de la noria
	GLfloat brazoLen = (casaX - L / 2) - noriaX; // distancia pared a centro noria
	LowPolyBox* brazoNoria = new LowPolyBox(1, stoneMat);
	brazoNoria->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(noriaX + brazoLen / 2, noriaR, casaZ))
		* glm::scale(glm::mat4(1.0f), glm::vec3(brazoLen, 8.0f, 8.0f)));
	gObjects.push_back(brazoNoria);

	// ============================================================
	// RIO
	// ============================================================
	mRiver = new WaterEntity(80, 1500, 30, waterMat);
	mRiver->setModelMat(glm::translate(glm::mat4(1.0f),
		glm::vec3(noriaX - 30, 3, casaZ)));
	gObjects.push_back(mRiver);

	// ============================================================
	// LAKE
	// ============================================================
	Lake* mLake = new Lake(300, 100, 100, texManager->getTexture("lake.jpg"));
	mLake->setModelMat(glm::translate(glm::mat4(1.0f),
		glm::vec3(noriaX - 30, 3, 1050 + casaZ)));
	mLake->setModelMat(glm::rotate(mLake -> modelMat(), float(glm::radians(90.0f)),
		glm::vec3(0, 1, 0)));
	gObjects.push_back(mLake);


	// ============================================================
	// Banco (malla indexada) 
	// ============================================================
	Bench* banco = new Bench(50.0, benchMat);
	banco->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(casaX + 100, 0, 90))
		* glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0, 1, 0)));
	gObjects.push_back(banco);

	// ============================================================
	// Barril
	// ============================================================
	Barrel* barril = new Barrel(35.0, 11.0, clayMat);
	barril->setModelMat(glm::translate(glm::mat4(1.0f),
		glm::vec3(casaX + 85, 0, 45)));
	gObjects.push_back(barril);

	// ============================================================
	// Rocas junto al rio
	// ============================================================
	LowPolySphere* roca1 = new LowPolySphere(14, 4, 5, rockMat);
	roca1->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(noriaX - 30, 5, 90))
		* glm::scale(glm::mat4(1.0f), glm::vec3(1.3f, 0.6f, 1.0f)));
	gObjects.push_back(roca1);

	LowPolySphere* roca2 = new LowPolySphere(10, 3, 4, rockMat);
	roca2->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(noriaX + 35, 4, 110))
		* glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.5f, 0.8f)));
	gObjects.push_back(roca2);

	LowPolySphere* roca3 = new LowPolySphere(7, 3, 3, rockMat);
	roca3->setModelMat(glm::translate(glm::mat4(1.0f),
		glm::vec3(noriaX - 20, 3, 130)));
	gObjects.push_back(roca3);

	// ============================================================
	// Montanas de fondo
	// ============================================================
	// Fondo izquierda
	Mountain* m1 = new Mountain(420, 330, 0, 4, 5, texManager->getTexture("montana2.jpg"));
	m1->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(-350, 0, -550)));
	gObjects.push_back(m1);

	// Fondo centro-izquierda
	Mountain* m2 = new Mountain(370, 280, 0, 4, 4, texManager->getTexture("montana2.jpg"));
	m2->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, -650)));
	gObjects.push_back(m2);

	// Fondo centro
	Mountain* m3 = new Mountain(450, 340, 0, 4, 6, texManager->getTexture("montana2.jpg"));
	m3->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(120, 0, -680)));
	gObjects.push_back(m3);

	// Fondo centro-derecha
	Mountain* m4 = new Mountain(380, 290, 0, 4, 4, texManager->getTexture("montana2.jpg"));
	m4->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(340, 0, -600)));
	gObjects.push_back(m4);

	// Fondo derecha
	Mountain* m5 = new Mountain(400, 310, 0, 4, 5, texManager->getTexture("montana2.jpg"));
	m5->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(530, 0, -480)));
	gObjects.push_back(m5);

	// Lateral izquierdo (cierra la U)
	Mountain* m6 = new Mountain(350, 270, 0, 4, 5, texManager->getTexture("montana2.jpg"));
	m6->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(-480, 0, -350)));
	gObjects.push_back(m6);

	// Lateral derecho (cierra la U)
	Mountain* m7 = new Mountain(360, 280, 0, 4, 5, texManager->getTexture("montana2.jpg"));
	m7->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(620, 0, -300)));
	gObjects.push_back(m7);
}

void SceneFinal::render(Camera const& cam) const
{
	cam.upload();

	const char* shaderNames[] = { "light", "lowpoly", "water" };
	for (const char* name : shaderNames) {
		Shader* sh = Shader::get(name);
		sh->use();
		for (Light* light : gLights)
			light->upload(*sh, cam.viewMat());
	}

	for (Abs_Entity* el : gObjects)
		el->render(cam.viewMat());

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	for (Abs_Entity* el : gtObjects)
		el->render(cam.viewMat());
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

void SceneFinal::load()
{
	Scene::load();
	glClearColor(0.02f, 0.02f, 0.06f, 1.0f);
}

void SceneFinal::unload()
{
	Scene::unload();
	glClearColor(0.6f, 0.7f, 0.8f, 1.0f);
}

void SceneFinal::update()
{
	Scene::update();
	if (mRiver) mRiver->update();
	if (mLantern) mLantern->update();
}

bool SceneFinal::handleEvents(unsigned int key)
{
	Scene::handleEvents(key);
	bool need_redisplay = true;
	switch (key) {
	case 'f':
		if (mLantern) mLantern->lightOnOff();
		break;
	case 'g':
		if (mMoonLight) mMoonLight->setEnabled(!mMoonLight->enabled());
		break;
	case 'n':
		LowPolyEntity::toggleWireframe();
		break;
	default:
		need_redisplay = false;
		break;
	}
	return need_redisplay;
}