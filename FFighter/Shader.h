#pragma once
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "utilities.h"
#include "Camera.h"
#include <map>

class Shader
{
public:
	Shader(std::string loaderPath);
	Shader::Shader(int N, GLenum* types, std::string* paths);
	Shader(int N, GLenum* types, std::string** paths, int* nFiles = nullptr);
	~Shader();
	void use();
	void off();
	GLuint getID();
	GLuint getUniformLocation(const char* name);
private:
	GLuint createProgram(const int N, GLuint* shaderIDs);
	GLuint loadShader(GLenum type, const int N, std::string* shaderPath);
	GLuint _programID;
	std::string readFile(const std::string pathToFile);
};

