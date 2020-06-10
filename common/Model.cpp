#include <iostream>
#include <assert.h>
#include <glm/vec2.hpp> // vec2, bvec2, dvec2, ivec2 and uvec2
#include <glm/vec3.hpp> // vec3, bvec3, dvec3, ivec3 and uvec3
#include <glm/vec4.hpp> // vec4, bvec4, dvec4, ivec4 and uvec4

//#include "Mesh.h"
#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

using namespace OpenGLSandbox::Common;

Model::Model(const std::string &path) : numVertices_(0), numIndices_(0), numMeshes_(0)
{
    loadModel(path);
}

void Model::loadModel(const std::string &path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    // retrieve the directory path of the filepath
    directory_ = path.substr(0, path.find_last_of('/'));

    // process ASSIMP's root node recursively
    // container for all meshes
    // allocated in stack because it is not needed after uploaded to the gpu buffers

    std::vector<glm::vec3> pos;
    std::vector<glm::vec2> tex;
    std::vector<glm::vec3> normal;
    std::vector<glm::vec3> tangent;
    std::vector<glm::vec3> bigent;

    std::vector<unsigned int> indices;

    buildMeshEntry(scene->mRootNode, scene);

    pos.resize(numVertices_);
    tex.resize(numVertices_);
    normal.resize(numVertices_);
    tangent.resize(numVertices_);
    bigent.resize(numVertices_);
    indices.resize(numIndices_);

    readNode(scene->mRootNode, scene, pos, tex, normal, tangent, bigent, indices);
}

void Model::buildMeshEntry(aiNode *root, const aiScene *scene)
{
    unsigned int verticeBaseIndex = 0;
    unsigned int indexBaseIndex = 0;
    glm::mat4 concatTransform = glm::mat4(1.0f);
    readNodePrepass(root, scene, verticeBaseIndex, indexBaseIndex, concatTransform);
}

void Model::readNodePrepass(aiNode *node,
                            const aiScene *scene,
                            unsigned int &verticeBaseIndex,
                            unsigned int &indiceBaseIndex,
                            glm::mat4 const &parentConcatTransform)
{
    numMeshes_ += node->mNumMeshes;

    auto assimpTranform = node->mTransformation;
    glm::mat4 const nodeTransform = glm::mat4(
        glm::vec4(assimpTranform.a1, assimpTranform.a2, assimpTranform.a3, assimpTranform.a4),
        glm::vec4(assimpTranform.b1, assimpTranform.b2, assimpTranform.b3, assimpTranform.b4),
        glm::vec4(assimpTranform.c1, assimpTranform.c2, assimpTranform.c3, assimpTranform.c4),
        glm::vec4(assimpTranform.d1, assimpTranform.d2, assimpTranform.d3, assimpTranform.d4));

    auto concateTransform = parentConcatTransform * nodeTransform;

    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

        MeshEntry meshEntry;
        meshEntry.verticeBaseIndex_ = verticeBaseIndex;
        meshEntry.indiceBaseIndex_ = indiceBaseIndex;
        meshEntry.name_ = std::string(mesh->mName.C_Str());
        meshEntry.materialIndex_ = mesh->mMaterialIndex;
        meshEntry.concatTransform_ = concateTransform;

        numVertices_ += mesh->mNumVertices;
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            numIndices_ += face.mNumIndices;
            meshEntry.numIndices_ += face.mNumIndices;
        }

        verticeBaseIndex += numVertices_;
        indiceBaseIndex += numIndices_;

        assert(meshEntriesMap_.find(meshEntry.name_) != meshEntriesMap_.end());
        meshEntriesMap_[meshEntry.name_] = meshEntry;
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        readNodePrepass(node->mChildren[i], scene, verticeBaseIndex, indiceBaseIndex, concateTransform);
    }
}

// iterate a tree, there is no dep between any nodes.
void Model::readNode(aiNode *node,
                     const aiScene *scene,
                     std::vector<glm::vec3> &pos,
                     std::vector<glm::vec2> &tex,
                     std::vector<glm::vec3> &normal,
                     std::vector<glm::vec3> &tangent,
                     std::vector<glm::vec3> &bigent,
                     std::vector<unsigned int> &indices)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        readMesh(mesh, scene, pos, tex, normal, tangent, bigent, indices);
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        readNode(node->mChildren[i], scene, pos, tex, normal, tangent, bigent, indices);
    }
}

void Model::readMesh(aiMesh *mesh,
                     const aiScene *scene,
                     std::vector<glm::vec3> &pos,
                     std::vector<glm::vec2> &tex,
                     std::vector<glm::vec3> &normal,
                     std::vector<glm::vec3> &tangent,
                     std::vector<glm::vec3> &bigent,
                     std::vector<unsigned int> &indices)
{
    const std::string meshName(mesh->mName.C_Str());
    assert(meshEntriesMap_.find(meshName) != meshEntriesMap_.end());

    auto verticeBaseIndex = meshEntriesMap_[meshName].verticeBaseIndex_;
    auto indiceBaseIndex = meshEntriesMap_[meshName].indiceBaseIndex_;

    auto maxVerticeIndex = verticeBaseIndex + mesh->mNumVertices - 1;
    assert(pos.size() - 1 >= maxVerticeIndex);
    assert(normal.size() - 1 >= maxVerticeIndex);
    assert(tex.size() - 1 >= maxVerticeIndex);
    assert(tangent.size() - 1 >= maxVerticeIndex);
    assert(bigent.size() - 1 >= maxVerticeIndex);

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        pos[verticeBaseIndex].x = mesh->mVertices[i].x;
        pos[verticeBaseIndex].y = mesh->mVertices[i].y;
        pos[verticeBaseIndex].z = mesh->mVertices[i].z;

        normal[verticeBaseIndex].x = mesh->mVertices[i].x;
        normal[verticeBaseIndex].y = mesh->mVertices[i].y;
        normal[verticeBaseIndex].z = mesh->mVertices[i].z;

        // texture coordinates
        // multiple texture coordinates? To Do
        if (mesh->mTextureCoords[0])
        {
            tex[verticeBaseIndex].x = mesh->mTextureCoords[0][i].x;
            tex[verticeBaseIndex].y = mesh->mTextureCoords[0][i].y;
        }
        // tangent
        tangent[verticeBaseIndex].x = mesh->mTangents[i].x;
        tangent[verticeBaseIndex].y = mesh->mTangents[i].y;
        tangent[verticeBaseIndex].z = mesh->mTangents[i].z;

        // bitangent
        bigent[verticeBaseIndex].x = mesh->mBitangents[i].x;
        bigent[verticeBaseIndex].y = mesh->mBitangents[i].y;
        bigent[verticeBaseIndex].z = mesh->mBitangents[i].z;

        verticeBaseIndex++;
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const auto &face = mesh->mFaces[i];
        assert(indices.size() >= indiceBaseIndex + face.mNumIndices);
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices[indiceBaseIndex++] = face.mIndices[j];
        }
    }
    // process materials
    assert(meshEntriesMap_[meshName].materialIndex_ = mesh->mMaterialIndex);
    if (materials_.find(mesh->mMaterialIndex) == materials_.end())
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        readTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        readTextures(material, aiTextureType_SPECULAR, "texture_specular");
        readTextures(material, aiTextureType_NORMALS, "texture_normal");
    }

    //std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
}

void Model::readTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString path;
        mat->GetTexture(type, i, &path);
        auto texturePath = directory_ + '/' + std::string(path.C_Str());
        if(textures_.find(texturePath) != textures_.end()){
            continue;
        }
        textures_[texturePath] = std::make_unique<Texture>(GL_TEXTURE_2D, texturePath, typeName);
    }
}