#pragma once
#include "Display.h"
#include "Camera.h"
#include "Shader.h"
#include "Model.h"
#include "Light.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include "MasterRenderer.h"
#include "Entity.h"


class Game
{
public:
	Game();
	void run();
	~Game();
private:
	void init();
	void loop();
	void draw();
	void update();
	void pollEvents();
	Display* display;
	Camera* camera;
	Shader* shader;
	Model* madel;
	Light* light0;
	Light* light1;
	std::map<SDL_Keycode, bool> _inputMap;
	int _deltaTime;
	int _lastFrame;

	MasterRenderer* _masterRenderer;
	Entity* _entity;
	std::vector<Entity*> _entities;
};

