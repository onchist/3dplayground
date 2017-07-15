#pragma once
#include "Shader.h"
#include "Entity.h"
#include "Model.h"
#include <utility>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Renderer
{
public:
	Renderer(Shader* shader, glm::mat4 projectionMatrix);
	~Renderer();
	void render(std::map<Model*, std::list<Entity*>> entities);
private:
	Shader* _shader;
	void processMesh(Model* model, int n);
	void processModelMatrix(Entity* entity);
	glm::mat4 _projectionMatrix;
};

