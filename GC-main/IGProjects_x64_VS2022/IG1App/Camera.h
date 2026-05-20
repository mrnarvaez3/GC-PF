#ifndef _H_Camera_H_
#define _H_Camera_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Viewport.h"

class Camera
{
public:
	explicit Camera(Viewport* vp);
	~Camera() = default;

	// viewPort
	Viewport const& viewPort() const { return *mViewPort; };

	// view matrix
	glm::mat4 const& viewMat() const { return mViewMat; };

	void set2D();
	void set3D();

	void pitch(GLfloat a); // rotates a degrees on the X axis
	void yaw(GLfloat a);   // rotates a degrees on the Y axis
	void roll(GLfloat a);  // rotates a degrees on the Z axis

	// Apartado 45
	void pitchReal(GLfloat a); // rotates a degrees on the X axis
	void yawReal(GLfloat a);   // rotates a degrees on the Y axis
	void rollReal(GLfloat a);  // rotates a degrees on the Z axis

	// projection matrix
	glm::mat4 const& projMat() const { return mProjMat; };

	// sets scene visible area size
	void setSize(GLdouble xw, GLdouble yh);
	// updates the scale factor
	void setScale(GLdouble s);

	// transfers its viewport, the view matrix and projection matrix to the GPU
	void upload() const;

	// Apartado 39
	// actualiamos mEye y mLook en función del movimiento
	void moveLR(GLfloat cs);
	void moveFB(GLfloat cs);
	void moveUD(GLfloat cs);

	// Apartado 41
	void changePrj();

	// Apartado 46
	void orbit(GLdouble incAng, GLdouble incY);
	// Apartado 48
	void setCenital();

protected:
	float dis = 500.0f;
	glm::vec3 mEye = {0.0, 0.0, dis}; // camera's position
	glm::vec3 mLook = {0.0, 0.0, 0.0};  // target's position
	glm::vec3 mUp = {0.0, 1.0, 0.0};    // the up vector

	// Apartado 38
	glm::vec3 mRight;
	glm::vec3 mUpward;
	glm::vec3 mFront;

	glm::mat4 mViewMat;   // view matrix = inverse of modeling matrix
	void uploadVM() const; // transfers viewMat to the GPU

	glm::mat4 mProjMat;   // projection matrix
	void uploadPM() const; // transfers projMat to the GPU

	GLfloat xRight, xLeft, yTop, yBot;     // size of scene visible area
	GLfloat mNearVal = 200, mFarVal = 10000; // view volume
	GLfloat mScaleFact = 1;                // scale factor
	bool bOrto = true;                      // orthogonal or perspective projection

	Viewport* mViewPort; // the viewport

	void setVM();
	void setPM();
	// Apartado 38
	void setAxes();
	glm::vec3 row(glm::mat4 matV, int col);

	GLdouble mAng = -45;
	GLdouble mRadio = 1000;

private:
	float distance = glm::length(mLook - mEye);
	float yawA = 0.0f;
	float pitchA = 0.0f;
	float rollA = 0.0f;

};

#endif //_H_Camera_H_
