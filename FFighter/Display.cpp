#include "Display.h"

bool Display::_bStarted = false;

Display::Display(std::string windowName, int width, int height) : _w(width), _h(height)
{
	if (!_bStarted) {
		SDL_Init(0);
		SDL_InitSubSystem(SDL_INIT_VIDEO);
		_bStarted = true;
	}
	_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, _w, _h, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {

	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	//SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
	//création du contexte openGl avec notre fenetre et error checking
	_glContext = SDL_GL_CreateContext(_window);
	if (_glContext == nullptr) {
		//insert error handling
	}
	//pour faire fonctionner opengl > 3
	glewExperimental = true;

	//initialisation de glew et error checking
	if (glewInit() != GLEW_OK) {
		//insert error handling
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//mise en place du double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);

	SDL_GL_SetSwapInterval(0);
	//couleur de fond d'écran au glClear()
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Display::swapBuffers() {
	SDL_GL_SwapWindow(_window);
}

void Display::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


Display::~Display()
{
}

int Display::getW()
{
	return _w;
}

int Display::getH()
{
	return _h;
}
