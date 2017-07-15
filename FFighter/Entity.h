#pragma once
#include "Model.h"
#include <glm/glm.hpp>

class Entity
{
public:
	Entity(Model* model, glm::vec3 position);
	~Entity();
	Model* getModel();
	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::quat getQuaternion();
private:
	Model* _model;
	glm::vec3 _position;
	glm::vec3 _scale;
	glm::quat _quaternion;
};

