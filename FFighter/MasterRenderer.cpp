#include "MasterRenderer.h"



MasterRenderer::MasterRenderer(Display* display, Shader* shader):_display(display), _shader(shader)
{
	createProjectionMatrix();
	_renderer = new Renderer(_shader, _projectionMatrix);
}


MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::addEntity(Entity * entity)
{
	std::list<Entity*>* currEntities = &_entityPool[entity->getModel()];
	currEntities->push_back(entity);
}

void MasterRenderer::render(std::list<Light*> lights, Camera * camera)
{
	clear();
	
	glEnable(GL_DEPTH_TEST);
	_shader->use();
	loadLights(_shader, lights);
	loadViewMatrix(_shader, camera);
	_renderer->render(_entityPool);
	_shader->off();
	_entityPool.clear();
}

void MasterRenderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.75f, 1.0f, 0.0f);
}

void MasterRenderer::createProjectionMatrix()
{
	_projectionMatrix = glm::perspective(glm::radians(FOV), (float)_display->getW() / (float)_display->getH(), NEAR_PLANE, FAR_PLANE);
}

void MasterRenderer::loadLights(Shader* shader, std::list<Light*> lights)
{
	for (std::list<Light*>::iterator it = lights.begin(); it != lights.end(); it++) {
		Light* light = *it;
		light->processUniforms(shader, 0);
	}
}

void MasterRenderer::loadViewMatrix(Shader * shader, Camera * camera)
{
	GLuint viewLocation = shader->getUniformLocation("view");
	glm::mat4 viewMatrix = camera->getViewMatrix(1.0f);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}


