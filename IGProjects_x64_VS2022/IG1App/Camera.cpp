#include "Shader.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Camera::Camera(Viewport* vp)
  : mViewMat(1.0)
  , mProjMat(1.0)
  , xRight(vp->width() / 2.0)
  , xLeft(-xRight)
  , yTop(vp->height() / 2.0)
  , yBot(-yTop)
  , mViewPort(vp)
{
	setPM();
}

void
Camera::uploadVM() const
{
	Shader::setGlobals(mViewMat);
}

// Apartado 38
void Camera::setAxes()
{
	mRight = row(mViewMat, 0);
	mUpward = row(mViewMat, 1);
	mFront = -row(mViewMat, 2);
}

// Apartado 39
void Camera::moveLR(GLfloat cs)
{
	mEye += mRight * cs;
	mLook += mRight * cs;
	setVM();
}

// Apartado 39
void Camera::moveFB(GLfloat cs)
{
	mEye += mFront * cs;
	mLook += mFront * cs;
	setVM();
}

// Apartado 39
void Camera::moveUD(GLfloat cs)
{
	mEye += mUpward * cs;
	mLook += mUpward * cs;
	setVM();
}

// Apartado 41
void Camera::changePrj()
{
	// modificamos bOrto
	bOrto = !bOrto;
	// actualizamos la proyeccion
	setPM();
}

// Apartado 46
void Camera::orbit(GLdouble incAng, GLdouble incY) {
	mAng += incAng;
	mEye.x = mLook.x + cos(radians(mAng)) * mRadio;
	mEye.z = mLook.z - sin(radians(mAng)) * mRadio;
	mEye.y += incY;
	// actualizar up

	setVM();
}

// Apartado 48
void Camera::setCenital()
{
	// Colocamos el eye y el look como mirando desde arriba
	mEye = glm::vec3(0.0f, 1000.0f, 0.0f);
	mLook = { 0, 0, 0 };
	mUp = glm::vec3(0.0f, 0.0f, -1.0f); // o (1,0,0)
	mAng = -90.0f;
	mRadio = glm::length(mLook - mEye);
	setVM();
}

void
Camera::setVM()
{
	mViewMat = lookAt(mEye, mLook, mUp); // glm::lookAt defines the view matrix
	setAxes();
}

void
Camera::set2D()
{
	mEye = {0, 0, 500};
	mLook = {0, 0, 0};
	mUp = {0, 1, 0};
	mAng = -90.0f;
	mRadio = glm::length(mLook - mEye);
	setVM();
}

void
Camera::set3D()
{
	mEye = {500, 500, 500};
	mLook = {0, 10, 0};
	mUp = {0, 1, 0};
	mAng = -45.0f;
	mRadio = glm::length(mLook - mEye);
	setVM();
}

void
Camera::pitch(GLfloat a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::vec3(0, 0, 1));
}

void
Camera::yaw(GLfloat a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::vec3(0, 1.0, 0));
}

void
Camera::roll(GLfloat a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::vec3(0, 0, 1.0));
}

// Apartado 45
void Camera::pitchReal(GLfloat a)
{
	// Eje X
	float angle = glm::radians(a);

	glm::vec3 dir = glm::normalize(mLook - mEye);
	glm::vec3 right = glm::normalize(glm::cross(dir, mUp));

	glm::mat3 rot = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, right));
	dir = rot * dir;

	mLook = mEye + dir * glm::length(mLook - mEye);
	mUp = glm::normalize(glm::cross(right, dir));

	setVM();
}

// Apartado 45
void Camera::yawReal(GLfloat a)
{
	// Eje Y
	float angle = glm::radians(a);

	glm::vec3 dir = glm::normalize(mLook - mEye);

	glm::mat3 rot = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, mUp));
	dir = rot * dir;

	mLook = mEye + dir * glm::length(mLook - mEye);

	glm::vec3 right = glm::normalize(glm::cross(dir, mUp));
	mUp = glm::normalize(glm::cross(right, dir));

	setVM();
}

// Apartado 45
void Camera::rollReal(GLfloat a)
{
	// Eje Z 
	float angle = glm::radians(a);

	glm::vec3 dir = glm::normalize(mLook - mEye);
	glm::vec3 right = glm::normalize(glm::cross(dir, mUp));
	glm::vec3 up = glm::normalize(glm::cross(right, dir));

	glm::mat3 rot = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, dir));
	right = rot * right;
	up = rot * up;

	mUp = up;
	
	setVM();
}

void
Camera::setSize(GLdouble xw, GLdouble yh)
{
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}

void
Camera::setScale(GLdouble s)
{
	mScaleFact -= s;
	if (mScaleFact < 0)
		mScaleFact = 0.01;
	setPM();
}

void
Camera::setPM()
{
	if (bOrto) { //  if orthogonal projection
		mProjMat = ortho(xLeft * mScaleFact,
		                 xRight * mScaleFact,
		                 yBot * mScaleFact,
		                 yTop * mScaleFact,
		                 mNearVal,
		                 mFarVal);
		// glm::ortho defines the orthogonal projection matrix
	}
	else {
		mProjMat = frustum(xLeft * mScaleFact,
						   xRight * mScaleFact,
						   yBot * mScaleFact,
						   yTop * mScaleFact,
						   mNearVal, 
						   mFarVal);
	}
}

// Apartado 38
glm::vec3 Camera::row(glm::mat4 matV, int col)
{
	return glm::vec3(matV[0][col], matV[1][col], matV[2][col]); 
}

void
Camera::uploadPM() const
{
	Shader::setGlobals(mProjMat);
}

void
Camera::upload() const
{
	mViewPort->upload();
	uploadVM();
	uploadPM();
	// Apartado 58
	//Shader* shader = Shader::get("simple_light"); 
	// Se fija el atributo uniforme del shader a las coordenadas homogeneas
	//glm::vec4 lighVec = mViewMat * glm::vec4(-1.0f, -1.5f, -1.25f, 0.0f);
	//shader->use();
	//shader->setUniform("lightDir", glm::normalize(lighVec));
}


