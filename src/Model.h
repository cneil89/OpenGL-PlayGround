#pragma once
#include "defines.h"
#include "Shader.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

uint32_t TextureFromFile(const std::string &path, const std::string &directory, bool gamma = false);

class Model
{
public:
    std::vector<TextureStruct> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;

    Model(const std::string &path);
    void Draw(Shader &shader);

private:
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<TextureStruct> loadMaterialTextures(aiMaterial *mat,
                                                    aiTextureType type, std::string typeName);

private:
};