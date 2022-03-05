#pragma once

#include <assimp/scene.h>
#include <string>
#include <vector>
#include <memory>

#include "Mesh.h"
#include "Texture.h"

/// <summary>
/// 模型（可由多个网格组成）
/// </summary>
class Model
{
public:
	Model(const std::string& modelPath);

	const std::vector<class Mesh>& GetMeshes() const { return m_meshes; }

private:
	void LoadModel(const std::string& path);

	std::vector<class Mesh> m_meshes;
	std::string m_directory;

	void TraverseNode(aiNode* node, const aiScene* scene);
	class Mesh GenerateMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<struct Vertex> GenerateVertexes(aiMesh* mesh) const;
	std::vector<unsigned int> GenerateIndices(aiMesh* mesh) const;
	std::vector<std::shared_ptr<class Texture>> GenerateTextures(aiMesh* mesh, const aiScene* scene) const;
	std::vector<std::shared_ptr<class Texture>> LoadMaterialTextures(
		aiMaterial* matrial, aiTextureType type, const std::string& name) const;
};

