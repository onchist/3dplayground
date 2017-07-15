#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <map>
#include <list>
#include "Display.h"
#include "Model.h"
#include "Shader.h"
#include "Entity.h"
#include "Renderer.h"
#include "Light.h"
#include "Camera.h"
class MasterRenderer
{
public:
	MasterRenderer(Display* display, Shader* shader);
	~MasterRenderer();
	void addEntity(Entity* entity);
	void render(std::list<Light*> lights, Camera* camera);
	void clear();
private:
	Display* _display;
	float FOV = 45.0f;
	float NEAR_PLANE = 0.1f;
	float FAR_PLANE = 100.0f;
	glm::mat4 _projectionMatrix;
	Shader* _shader;
	Renderer* _renderer;

	std::map<Model*, std::list<Entity*>> _entityPool;

	void createProjectionMatrix();
	void loadLights(Shader* shader, std::list<Light*> lights);
	void loadViewMatrix(Shader* shader, Camera* camera);
};

