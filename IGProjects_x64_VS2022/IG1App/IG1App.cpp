#include "IG1App.h"

#include <iostream>

#include "Escenas/Scene1.h"
#include "Escenas/Scene2.h"
#include "Escenas/Scene3.h"
#include "Escenas/Scene4.h"
#include "Escenas/Scene5.h"
#include "Escenas/Scene6.h"
#include "Escenas/Scene7.h"
#include "Escenas/Scene8.h"
#include "Escenas/Scene9.h"
#include "Escenas/Scene10.h"
#include "Escenas/SceneFinal.h"
#include "Texture.h"
#include "Entidades/ColorMaterialEntity.h"

using namespace std;

// static single instance (singleton pattern)
IG1App IG1App::s_ig1app; // default constructor (constructor with no parameters)

// Print OpenGL errors and warnings
void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                   GLsizei length, const GLchar* message, const void* userParam)
{
	if (severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
		const char* prefix = (type == GL_DEBUG_TYPE_ERROR)
			? "\x1b[31m[ERROR]\x1b[0m "
			: "\x1b[33m[WARNING]\x1b[0m ";
		cout << prefix << message << endl;
	}
}

// Print GLFW errors
void glfwErrorCallback(int error_code, const char* description)
{
	cout << "\x1b[33m[GLFW]\x1b[0m " << description << endl;
}

void
IG1App::close()
{
	cout << "Closing GLFW...\n";
	glfwSetWindowShouldClose(mWindow, true); // stops main loop
}

void
IG1App::run() // enters the main event processing loop
{
	if (mWindow == 0) // if not intilialized
		init();

	// IG1App main loop
	while (!glfwWindowShouldClose(mWindow)) {
		// Redisplay the window if needed
		// Apartado 14
		if (mUpdateEnabled) { // comprobamos si está activo el update
			if (glfwGetTime() - mNextUpdate > FRAME_DURATION) { // comprobamos el tiempo del frame
				mNextUpdate = glfwGetTime();
				mScenes[mCurrentScene]->update();
				mNeedsRedisplay = true;
			}
			// Esperamos hasta el siguiente frame
			glfwWaitEventsTimeout(FRAME_DURATION - (glfwGetTime() - mNextUpdate)); 
		}
		else {
			// Stop and wait for new events
			glfwWaitEvents();

		}
		if (mNeedsRedisplay) {
			if (m2Vistas)
				display2V();
			else
				display();

			if (mCurrentScene == 4)
				static_cast<Scene4*>(mScenes[mCurrentScene])->photoUpdate();
			else if (mCurrentScene != 8)
				mNeedsRedisplay = false;
		}
	}

	destroy();
}

void
IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH);
	mCamera = new Camera(mViewPort);
	mCamera2 = new Camera(mViewPort);
	currentCamera = mCamera;
	mScenes.push_back(new SceneFinal);

	// Apartado 6
	mScenes.push_back(new Scene1);
	mScenes.push_back(new Scene2);
	mScenes.push_back(new Scene3);
	mScenes.push_back(new Scene4);
	mScenes.push_back(new Scene5);
	mScenes.push_back(new Scene6);
	mScenes.push_back(new Scene7);
	mScenes.push_back(new Scene8);
	mScenes.push_back(new Scene9);

	currentCamera->set2D();

	// Inicializacion
	int numScenes = 10;
	for (int i = 0; i < numScenes; i++)
		mScenes[i]->init();
	mScenes[mCurrentScene]->load();

	photos = new Texture();
}

void
IG1App::iniWinOpenGL()
{ // Initialization
	cout << "Starting GLFW...\n";

	glfwSetErrorCallback(glfwErrorCallback);
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // enable on macOS
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Create window with its associated OpenGL context, return window's pointer
	mWindow = glfwCreateWindow(mWinW, mWinH, "IG1App", nullptr, nullptr);

	if (mWindow == nullptr) {
		glfwTerminate();
		throw std::logic_error("cannot create GLFW window");
	}

	glfwMakeContextCurrent(mWindow);

	// Initialize OpenGL extension library
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		glfwTerminate();
		throw std::logic_error("Error while loading extensions");
	}

	// Callback registration
	glfwSetWindowSizeCallback(mWindow, s_resize);
	glfwSetCharCallback(mWindow, s_key);
	glfwSetKeyCallback(mWindow, s_specialkey);
	glfwSetWindowRefreshCallback(mWindow, s_display);

	glfwSetMouseButtonCallback(mWindow, s_mouse);
	glfwSetCursorPosCallback(mWindow, s_motion);
	glfwSetScrollCallback(mWindow, s_mouseWheel);

	// Error message callback (all messages)
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0u, 0, GL_TRUE);
	glDebugMessageCallback(debugCallback, nullptr);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}

void
IG1App::destroy()
{ // release memory and resources

	delete(photos);

	for (Scene* scene : mScenes)
		delete scene;
	mScenes.clear();

	delete mCamera;
	delete mCamera2;
	mCamera = nullptr;
	mCamera2 = nullptr;
	currentCamera = nullptr;
	delete mViewPort;
	mViewPort = nullptr;

	Shader::destroy();

	glfwTerminate();
}

void
IG1App::display() const
{ // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer

	mScenes[mCurrentScene]->render(*currentCamera); // uploads the viewport and camera to the GPU

	glfwSwapBuffers(mWindow); // swaps the front and back buffer
}

void
IG1App::display2V()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer

	//Camera auxCam = *mCamera; // copiando mCamera
	Viewport auxVP = *mViewPort;
	mViewPort->setSize(mWinW / 2, mWinH);
	mCamera->setSize(mViewPort->width(), mViewPort->height());
	mCamera2->setSize(mViewPort->width(), mViewPort->height());

	int auxCurrent = mCurrentScene;

	// mitad izquierda
	mViewPort->setPos(0, 0);

	changeScene(leftIndex);
	mScenes[leftIndex]->render(*(mCamera));

	// mitad derecha
	mViewPort->setPos(mViewPort->width(), 0);
	
	changeScene(rightIndex);
	mScenes[rightIndex]->render(*(mCamera2));

	changeScene(auxCurrent);

	*mViewPort = auxVP; // * restaurar el puerto de vista
	mCamera->setSize(mViewPort->width(), mViewPort->height());
	mCamera2->setSize(mViewPort->width(), mViewPort->height());

	glfwSwapBuffers(mWindow); // swaps the front and back buffer
}

void
IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth;
	mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	currentCamera->setSize(mViewPort->width(), mViewPort->height());
}

void
IG1App::key(unsigned int key)
{
	bool need_redisplay = true;
	bool sceneBool = false;

	sceneBool = mScenes[mCurrentScene]->handleEvents(key);
	switch (key) {		
		case '+':
			currentCamera->setScale(+0.01); // zoom in  (increases the scale)
			break;
		case 'a':
			currentCamera->moveLR(5.0f);
			break;
		case 'd':
			currentCamera->moveLR(-5.0f);
			break;
		case 'w':
			currentCamera->moveUD(-5.0f);
			break;
		case 's':
			currentCamera->moveUD(5.0f);
			break;
		case 'W':
			currentCamera->moveFB(-5.0f);
			break;
		case 'S':
			currentCamera->moveFB(5.0f);
			break;
		case 'p': // Apartado 43
			// cambiamos la proyeccion
			currentCamera->changePrj();
			break;
		case 'c': // Apartado 48 comprobacion
			// vista cenital
			currentCamera->setCenital();
			break;
		case '-':
			currentCamera->setScale(-0.01); // zoom out (decreases the scale)
			break;
		case 'l':
			currentCamera->set3D();
			break;
		case 'o':
			currentCamera->set2D();
			break;
		case 'j':
			currentCamera->setCenital();
			break;
		case 'U': // Apartado 12 activamos el update
			mUpdateEnabled = !mUpdateEnabled;
			break;
		case 'u': // Apartado 12 activamos el update
			mScenes[mCurrentScene]->update();
			break;
		case 'F': // Apartado 36 foto
			glfwGetWindowSize(mWindow, &mWinW, &mWinH);
			photos->loadColorBuffer(mWinW, mWinH);
			photos->createBMPFile("file.bmp", mWinW, mWinH);
			break;
		case 'k': // Apartado 49
			mCamera->set3D();
			mCamera2->set3D();
			m2Vistas = !m2Vistas;
			break;
		case 'N': // Apartado 63
			ColorMaterialEntity::toggleShowNormals();
			break;
		default:
			
			if (key >= '0' && key <= '9') {
				if (changeScene(key - '0')) {
					// cambio de escena con doble vista
					if (m2Vistas) {
						if (mousePos == 1)
							leftIndex = mCurrentScene;
						else
							rightIndex = mCurrentScene;
					}
					break;
				}
				cout << "[NOTE] There is no scene " << char(key) << ".\n";
			}
			need_redisplay = sceneBool;
			break;
	} // switch

	if (need_redisplay)
		mNeedsRedisplay = true;
}

void
IG1App::specialkey(int key, int scancode, int action, int mods)
{
	// Only interested in press events
	if (action == GLFW_RELEASE)
		return;

	bool need_redisplay = true;

	// Handle keyboard input
	// (key reference: https://www.glfw.org/docs/3.4/group__keys.html)
	switch (key) {
		case GLFW_KEY_ESCAPE:                     // Escape key
			glfwSetWindowShouldClose(mWindow, true); // stops main loop
			break;
		case GLFW_KEY_RIGHT:
			if (mods == GLFW_MOD_CONTROL)
				currentCamera->rollReal(-1); // rotates -1 on the X axis
			else
				currentCamera->yawReal(1); // rotates 1 on the X axis
			break;
		case GLFW_KEY_LEFT:
			if (mods == GLFW_MOD_CONTROL)
				currentCamera->rollReal(1); // rotates 1 on the Y axis
			else
				currentCamera->yawReal(-1); // rotate -1 on the Y axis
			break;
		case GLFW_KEY_UP:
			currentCamera->pitchReal(1); // rotates 1 on the Z axis
			break;
		case GLFW_KEY_DOWN:
			currentCamera->pitchReal(-1); // rotates -1 on the Z axis
			break;
		default:
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		mNeedsRedisplay = true;
}

void IG1App::s_mouse(GLFWwindow* win, int button, int action, int mods)
{
	s_ig1app.mouse(button, action, mods);
}

void IG1App::s_motion(GLFWwindow* win, double x, double y)
{
	s_ig1app.motion(x, y);
}

void IG1App::s_mouseWheel(GLFWwindow* win, double dx, double dy)
{
	s_ig1app.mouseWheel(dx, dy);
}

void IG1App::mouse(int button, int state, int mods)
{
	// calculo posicion
	int height;
	double x, y;
	glfwGetWindowSize(mWindow, nullptr, &height);
	glfwGetCursorPos(mWindow, &x, &y);
	y = height - y;
	
	// pulsación
	if (state == GLFW_PRESS) {
		mMouseButt = button;
	}
	else if (state == GLFW_RELEASE) { // soltar
		mMouseButt = -1;
	}

	mMouseCoord = glm::dvec2(x, y);
}

void IG1App::motion(double x, double y)
{
	int height;
	glfwGetWindowSize(mWindow, nullptr, &height);

	y = height - y;

	glm::dvec2 mp = glm::dvec2(mMouseCoord.x - x, mMouseCoord.y - y);
	mMouseCoord = glm::dvec2(x, y);

	// boton izquierdo
	if (mMouseButt == GLFW_MOUSE_BUTTON_LEFT) {
		currentCamera->orbit(mp.x * 0.05f, mp.y);
	}
	// boton derecho
	if (mMouseButt == GLFW_MOUSE_BUTTON_RIGHT) {
		currentCamera->moveLR(mp.x);
		currentCamera->moveUD(mp.y);
	}

	// ventana en la que esta el ratón
	if (m2Vistas) {
		// parte izquierd
		if (x < mWinW / 2) {
			mousePos = 1;
			// gestion escena
			changeScene(leftIndex);
			// se asigna la camara
			currentCamera = mCamera;
		}
		else { // parte derecha
			mousePos = 2;
			// gestion escena
			changeScene(rightIndex);
			// se asigna la camara
			currentCamera = mCamera2;
		}
	}

	mNeedsRedisplay = true;
}

void IG1App::mouseWheel(double dx, double dy)
{
	// GLFW_KEY_LEFT_CONTROL
	int ctrlL = glfwGetKey(mWindow, GLFW_KEY_LEFT_CONTROL);
	int ctrlR = glfwGetKey(mWindow, GLFW_KEY_RIGHT_CONTROL);

	if (ctrlL == GLFW_PRESS || ctrlR == GLFW_PRESS) {
		currentCamera->setScale(dy * 0.05f);
	}
	else {
		currentCamera->moveFB(dy);
	}

	mNeedsRedisplay = true;
}

bool
IG1App::changeScene(size_t sceneNr)
{
	// Check whether the scene exists
 	if (sceneNr >= mScenes.size())
		return false;


	// Change only if a different scene
	if (sceneNr != mCurrentScene) {
		mScenes[mCurrentScene]->unload();
		mCurrentScene = sceneNr;
		mScenes[mCurrentScene]->load();
	}

	return true;
}
