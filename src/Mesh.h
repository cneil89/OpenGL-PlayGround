#pragma once
#include "defines.h"
#include "Shader.h"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define MAX_BONE_INFLUENCE 4

struct Vertex
{
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    // bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    // weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};

// TODO: Repurpose to use the Texture class
struct TextureStruct
{
    uint32_t id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<TextureStruct> textures;

    Mesh(std::vector<Vertex> verticies, std::vector<uint32_t> indicies, std::vector<TextureStruct> textures);
    void Draw(Shader &shader);

private:
    uint32_t m_VAO, m_VBO, m_EBO;

    void setupMesh();
};