#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <SDL/SDL.h>

class Camera
{
public:
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f));
	~Camera();
	glm::mat4 getViewMatrix(float zoom);
	void setPos(glm::vec3 newPos);
	void move(glm::vec3 offset);
	void setAngles(glm::vec3 newAngles);
	void rotate(glm::vec3 rotate);

private:
	void update();
	glm::vec3 _position;
	glm::vec3 _eulerAngles;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _side;
	bool _bOutdated;
};

