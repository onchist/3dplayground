#pragma once
#include <string>
#include <SDL/SDL.h>
#include <GL/glew.h>

class Display
{
public:
	Display(std::string windowName, int width, int height);
	void swapBuffers();
	void clear();
	~Display();
	int getW();
	int getH();
private:
	static bool _bStarted;
	int _w;
	int _h;
	SDL_Window* _window;
	SDL_GLContext _glContext;
};

