#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
	delete display;
	delete madel;
	delete camera;
	delete shader;
}

void Game::run() {
	init();
	loop();
}

void Game::init() {
	display = new Display("Lul", 1280, 720);
	shader = new Shader("shaders/base.loader");
	camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f));
	madel = new Model("models/nanosuit/nanosuit.OBJ");
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	LightMaterial lightMat;
	lightMat.ambient = color * 0.1f;
	lightMat.diffuse = color * 0.7f;
	lightMat.specular = color;
	light1 = new DirLight(lightMat, glm::vec3(0.0f, 0.0f, 1.0f));

	_entities.push_back(new Entity(madel, glm::vec3(0.0f, 0.0f, 0.0f)));
	
	_masterRenderer = new MasterRenderer(display, shader);
}

void Game::loop() {
	while (true) {
		update();
		draw();
	}
}

void Game::draw() {
	display->clear();
		
	std::list<Light*> lights;
	lights.push_back(light1);
	for (int i = 0; i < _entities.size(); i++) {
		_masterRenderer->addEntity(_entities[i]);
	}
	_masterRenderer->render(lights, camera);
	_masterRenderer->clear();

	display->swapBuffers();
}

void Game::update() {
	_deltaTime = SDL_GetTicks() - _lastFrame;
	_lastFrame = SDL_GetTicks();
	pollEvents();
	if (_inputMap[SDLK_z]) {
		camera->move(glm::vec3(0.0f, 0.0f, (float)_deltaTime / 100.0f));
	}
	if (_inputMap[SDLK_s]) {
		camera->move(glm::vec3(0.0f, 0.0f, -(float)_deltaTime / 100.0f));
	}
	if (_inputMap[SDLK_q]) {
		camera->move(glm::vec3(-(float)_deltaTime / 100.0f,0.0f , 0.0f));
	}
	if (_inputMap[SDLK_d]) {
		camera->move(glm::vec3((float)_deltaTime / 100.0f, 0.0f, 0.0f));

	}
	if (_inputMap[SDLK_k]) {
		camera->rotate(glm::vec3(0.0f, (float)(M_PI / 1000.0f * (float)_deltaTime), 0.0f));
	}
	if (_inputMap[SDLK_m]) {
		camera->rotate(glm::vec3(0.0f, (float)(-M_PI / 1000.0f * (float)_deltaTime), 0.0f));
	}
	if (_inputMap[SDLK_o]) {
		camera->rotate(glm::vec3((float)(M_PI / 1000.0f * (float)_deltaTime), 0.0f, 0.0f));
	}
	if (_inputMap[SDLK_l]) {
		camera->rotate(glm::vec3((float)(-M_PI / 1000.0f * (float)_deltaTime), 0.0f, 0.0f));
	}
}

void Game::pollEvents() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			//_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			_inputMap[evnt.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			_inputMap[evnt.key.keysym.sym] = false;
			break;
		case SDL_MOUSEMOTION:
			break;
		}
	}
}