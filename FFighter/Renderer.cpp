#include "Renderer.h"



Renderer::Renderer(Shader * shader, glm::mat4 projectionMatrix) : _shader(shader), _projectionMatrix(projectionMatrix)
{
	

}

Renderer::~Renderer()
{
}

void Renderer::render(std::map<Model*, std::list<Entity*>> entities)
{
	
	GLuint projectionLoc = _shader->getUniformLocation("projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(_projectionMatrix));

	for (std::map<Model*, std::list<Entity*>>::iterator it = entities.begin();
		it != entities.end(); it++)
	{
		Model* current = std::get<0>(*it);
		for (int i = 0; i < current->getMeshCount(); i++) {
			processMesh(current, i);
			std::list<Entity*> entitiesCurr = std::get<1>(*it);
			for (std::list<Entity*>::iterator ot = entitiesCurr.begin();
				ot != entitiesCurr.end(); ot++) {
				processModelMatrix(*ot);
				glDrawElements(GL_TRIANGLES, current->getMeshIndicesSize(i), GL_UNSIGNED_INT, (GLvoid*)0);
			}
		}
	}
}


void Renderer::processMesh(Model * model, int n)
{
	model->setupMesh(_shader, n);
}

void Renderer::processModelMatrix(Entity * entity) {
	glm::mat4 model;
	model = glm::translate(model, entity->getPosition());
	model *= glm::toMat4(entity->getQuaternion());
	model = glm::scale(model, entity->getScale());

	GLuint modelLoc = _shader->getUniformLocation("model");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	GLint matShineLoc = _shader->getUniformLocation("material.shininess");
	glUniform1f(matShineLoc, 128.0f);
}