#include "Shader.h"

Shader::Shader(std::string loaderPath) {
	int N;
	std::vector<GLenum> types;
	std::vector<std::string> paths;

	std::string loaderText = utilities::utilReadFile(loaderPath);
	std::vector<std::string> loaderByLine = utilities::splitStr(loaderText, '\n');
	
	N = std::stoi(loaderByLine[0]);
	std::vector<std::string> vTypes = utilities::splitStr(loaderByLine[1], ' ');
	std::vector<std::string> vPaths = utilities::splitStr(loaderByLine[2], ' ');
	for (int i = 0; i < N; i++) {
		if (vTypes[i] == "VERTEX") {
			types.push_back(GL_VERTEX_SHADER);
		}
		else if (vTypes[i] == "FRAGMENT") {
			types.push_back(GL_FRAGMENT_SHADER);
		}
		paths = vPaths;
	}

	*this = Shader(N, &types[0], &paths[0]);
}

Shader::Shader(int N, GLenum* types, std::string* paths) {
	GLuint* shaderIDs = new GLuint[N];
	for (int i = 0; i < N; i++) {
		shaderIDs[i] = loadShader(types[i], 1, &paths[i]);
	}
	_programID = createProgram(N, shaderIDs);
}

Shader::Shader(int N, GLenum* types, std::string** paths, int* nFiles) {
    GLuint* shaderIDs = new GLuint[N];
	for (int i = 0; i < N; i++) {
		shaderIDs[i] = loadShader(types[i], nFiles[i], paths[i]);
	}
	_programID = createProgram(N, shaderIDs);
}


Shader::~Shader() {
}

void Shader::use() {
	glUseProgram(_programID);
}

void Shader::off()
{
	glUseProgram(0);
}

GLuint Shader::loadShader(GLenum type, const int N, std::string* shaderPaths) {

	bool aborted = false;
	//initialize the shader
	GLuint shaderID = glCreateShader(type);
	//array containing the content of the files (string)
	std::string *shaderCode = new std::string[N];
	//c_str of the shaderCode
	char** shaderCodeCstr = new char*[N];
	//array stocking the lenghts of the files
	GLint *lenght = new GLint[N];
	//for each file
	for (int i = 0; i < N; i++)
	{
		//load the content of the file into a string
		shaderCode[i] = readFile(shaderPaths[i]);
		//error handling in case opening fails
		if (shaderCode[i] == "") { std::cout << "problem loading the sources from " << shaderPaths[i] << std::endl; aborted = true; }
		//get the lenght of the content of the file
		lenght[i] = shaderCode[i].length();
		//convert to c_str in order to be used in glShaderSource()
		shaderCodeCstr[i] = (char*)shaderCode[i].c_str();
	}
	//if all sources loaded correctly
	if (!aborted) {
		//load the source in the shader
		glShaderSource(shaderID, N, shaderCodeCstr, lenght);
		//compile
		glCompileShader(shaderID);
		//success checking
		int success = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			std::cout << "returned by GL_COMPILE_STATUS : " << success << std::endl;
			int lenght = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &lenght);
			GLchar* errorLog;
			errorLog = new GLchar[lenght];
			glGetShaderInfoLog(shaderID, lenght, &lenght, errorLog);
			std::cout << errorLog << std::endl;
		}
	}
	return shaderID;
}

std::string Shader::readFile(const std::string pathToFile)
{
	std::ifstream t(pathToFile);
	if (t) { std::cout << "Stream with the file " << pathToFile << " succesfully openned." << std::endl; }

	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}

GLuint Shader::createProgram(const int N, GLuint* shaderIDs) {
	GLuint programID;
	programID = glCreateProgram();
	for (int i = 0; i < N; i++) {
		glAttachShader(programID, shaderIDs[i]);
	}
	glLinkProgram(programID);
	GLint success = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		utilities::PrintError("Error while linking a shader program.");
		return 0;
	}
	return programID;
}

GLuint Shader::getID() {
	return _programID;
}

GLuint Shader::getUniformLocation(const char* name) {
	return glGetUniformLocation(_programID, name);
}
