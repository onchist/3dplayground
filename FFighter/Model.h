#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GL/glew.h>
#include "Shader.h"
#include "Mesh.h"
#include <vector>
#include <string>
#include "utilities.h"


class Model {
public:
	Model(GLchar* path) {
		this->loadModel(path);
	}
	void draw(Shader* shader);
	void setupMesh(Shader* shader, int i);
	int getMeshCount();
	int getMeshIndicesSize(int n);
	Mesh* getMesh(int n);
private:
	std::vector<Mesh> _meshes;
	std::string _directory;
	std::vector<Texture> _texturesLoaded;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadTextures(aiMaterial* material, aiTextureType type, std::string typeName);
};