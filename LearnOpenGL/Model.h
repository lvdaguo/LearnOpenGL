#pragma once

#include <assimp/scene.h>
#include <string>
#include <vector>

#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	Model(const std::string& modelPath);

	const std::vector<class Mesh>& GetMeshes() const { return m_meshes; }

private:
	void LoadModel(const std::string& path);

	std::vector<class Mesh> m_meshes;
	std::string m_directory;

	void ProcessNode(aiNode* node, const aiScene* scene);
	class Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<class Texture> LoadMaterialTextures(aiMaterial* matrial, aiTextureType type, const std::string& name);
};

