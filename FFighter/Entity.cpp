#include "Entity.h"






Entity::Entity(Model * model, glm::vec3 position): _model(model), _position(position)
{
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Entity::~Entity()
{
}

Model * Entity::getModel()
{
	return _model;
}

glm::vec3 Entity::getPosition()
{
	return _position;
}

glm::vec3 Entity::getScale()
{
	return _scale;
}

glm::quat Entity::getQuaternion()
{
	return _quaternion;
}
