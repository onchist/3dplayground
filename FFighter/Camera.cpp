#include "Camera.h"



Camera::Camera(glm::vec3 pos) : _position(pos), _bOutdated(true)
{
	_front = glm::vec3(0.0f, 0.0f, 0.0f);
	_up = glm::vec3(0.0f, 1.0f, 0.0f);
	_side = glm::cross(_front, _up);
}


Camera::~Camera()
{
}

void Camera::setPos(glm::vec3 newPos) {
	_position = newPos;
}

void Camera::move(glm::vec3 offset)
{
	if (_bOutdated) {
		update();
	}
	glm::vec3 movementX = offset.x * _side;
	glm::vec3 movementY = offset.y * _up;
	glm::vec3 movementZ = offset.z * _front;
	glm::vec3 movement = movementX + movementY + movementZ;
	_position += movement;
}

void Camera::setAngles(glm::vec3 newAngles)
{
	_eulerAngles = newAngles;
	_bOutdated = true;
}

void Camera::rotate(glm::vec3 rotate)
{
	_eulerAngles += rotate;
	_bOutdated = true;
}



glm::mat4 Camera::getViewMatrix(float zoom) {
	glm::mat4 tm0, rm0, ret;

	tm0 = glm::translate(tm0, -_position);

	glm::quat quatX = glm::angleAxis(-_eulerAngles.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat quatY = glm::angleAxis(-_eulerAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat quatZ = glm::angleAxis(-_eulerAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::quat quat = quatX * quatY * quatZ;

	rm0 = glm::toMat4(quat);

	ret = rm0  * tm0;

	return ret;
}

void Camera::update(){
	float x = cos(_eulerAngles.x) * sin(_eulerAngles.y);
	float y = -sin(_eulerAngles.x);
	float z = cos(_eulerAngles.x) * cos(_eulerAngles.y);

	
	_front = -glm::vec3(x, y, z);
	_side = glm::cross(_front, _up);
	_bOutdated = false;
}