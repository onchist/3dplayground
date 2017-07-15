#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <vector>
#include <SDL/SDL.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#ifndef UTILITIES
#define UTILITIES
namespace utilities {
	std::vector<std::string> splitStr(std::string toSplit, char delimiter);
	std::string utilReadFile(const std::string pathToFile);
	void PrintError(std::string errorMessage);
	GLuint TextureFromFile(std::string path);
	GLuint TextureFromFile(const char* path, std::string directory);
	glm::quat quatFromEuler(glm::vec3 eulerAngles);
}
#endif