#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <iostream>
#include <unordered_map>

#include "Model.h"
//#include "Mesh.h"

Model::Model(const std::string& modelPath)
{
    LoadModel(modelPath);
}

void Model::LoadModel(const std::string& path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
    {
        std::cout << "加载模型错误:" << importer.GetErrorString() << std::endl;
        return;
    }
    m_directory = path.substr(0, path.find_last_of('/'));
    TraverseNode(scene->mRootNode, scene);
}

void Model::TraverseNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(GenerateMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; ++i)
    {
        TraverseNode(node->mChildren[i], scene);
    }
}

Mesh Model::GenerateMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertexes = GenerateVertexes(mesh);
    std::vector<unsigned int> indices = GenerateIndices(mesh);
    std::vector<std::shared_ptr<Texture>> textures = GenerateTextures(mesh, scene);
    return Mesh(vertexes, indices, textures);
}

std::vector<struct Vertex> Model::GenerateVertexes(aiMesh* mesh) const
{
    std::vector<Vertex> vertexes;
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex;
        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        vertex.normal.x = mesh->mNormals[i].x;
        vertex.normal.y = mesh->mNormals[i].y;
        vertex.normal.z = mesh->mNormals[i].z;

        // 网格是否有纹理坐标
        if (mesh->mTextureCoords[0])
        {
            vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
            vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
        }
        else 
        {
            vertex.texCoords = glm::vec2(0.0f);
        }

        vertexes.push_back(vertex);
    }
    return vertexes;
}

std::vector<unsigned int> Model::GenerateIndices(aiMesh* mesh) const
{
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }
    return indices;
}

std::vector<std::shared_ptr<class Texture>> Model::GenerateTextures(aiMesh* mesh, const aiScene* scene) const
{
    std::vector<std::shared_ptr<Texture>> textures;

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<std::shared_ptr<Texture>> diffuseMaps = 
        LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    std::vector<std::shared_ptr<Texture>> specularMaps = 
        LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");

    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    return textures;
}

std::vector<std::shared_ptr<class Texture>> Model::LoadMaterialTextures(
    aiMaterial* material, aiTextureType type, const std::string& textureType) const
{
    std::vector<std::shared_ptr<Texture>> textures;
    static std::unordered_map<std::string, std::shared_ptr<Texture>> loadedTextures;

    for (unsigned int i = 0; i < material->GetTextureCount(type); ++i)
    {
        aiString str;
        material->GetTexture(type, i, &str);
        std::string filename(str.C_Str());

        // 共享已经加载过的纹理
        auto it = loadedTextures.find(filename);
        if (it == loadedTextures.end())
        {
            std::string filepath = m_directory + '/' + filename;
            textures.push_back(std::make_shared<Texture>(filepath, textureType));
            loadedTextures.emplace(filename, textures.back());
        }
        else
        {
            textures.push_back(loadedTextures[filename]);
        }
    }

    return textures;
}
