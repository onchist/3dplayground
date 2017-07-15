#include "utilities.h"


std::vector<std::string> utilities::splitStr(std::string toSplit, char delimiter) {
	std::stringstream ss(toSplit);
	std::vector<std::string> ret;
	std::string newLine;

	while (std::getline(ss, newLine, delimiter)) {
		ret.push_back(newLine);
	}
	return ret;
}

//returns a string of the text file
std::string utilities::utilReadFile(const std::string pathToFile)
{
	std::ifstream t(pathToFile);
	if (t) { std::cout << "Stream with the file " << pathToFile << " succesfully openned." << std::endl; }

	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}

//simple error printing
void utilities::PrintError(std::string errorMessage) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
		"Fatal Error",
		errorMessage.c_str(),
		NULL);

}

GLuint utilities::TextureFromFile(std::string path)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return textureID;
}

GLuint utilities::TextureFromFile(const char* path, std::string directory)
{
	//Generate texture ID and load texture data 
	std::string filename = std::string(path);
	filename = directory + '/' + filename;
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	//std::cout << "Attempted to load file : " << directory + '/' + path << "w = " << width << " h = "<< height << std::endl;

	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return textureID;
}

glm::quat utilities::quatFromEuler(glm::vec3 eulerAngles) {
	glm::quat quatX = glm::angleAxis(eulerAngles.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat quatY = glm::angleAxis(eulerAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat quatZ = glm::angleAxis(eulerAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));

	return quatX * quatY * quatZ;
}