#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include <GLFW/glfw3.h>
#include <assimp/scene.h>
#include <glm/mat4x4.hpp>
#include "Texture.h"

namespace OpenGLSandbox
{
    namespace Common
    {
        class Texture;
        class Model
        {
        public:
            enum class IOPass
            {
                PrePass, // scan scene graph
                ReadPass // read real data
            };

            Model(const std::string &path);
            virtual ~Model(){};
            void draw(GLuint shaderProgram);

        protected:
            struct MeshEntry
            {
                inline static const unsigned int INVALID_MATERIAL = 0xFFFFFFFF;
                inline static const std::string UNDEFINED_NAME = "";
                MeshEntry()
                {
                    name_ = UNDEFINED_NAME;
                    numIndices_ = 0;
                    verticeBaseIndex_ = 0;
                    indiceBaseIndex_ = 0;
                    materialIndex_ = INVALID_MATERIAL;
                    concatTransform_ = glm::mat4(1.0f);
                }

                unsigned int numIndices_;
                unsigned int verticeBaseIndex_;
                unsigned int indiceBaseIndex_;
                unsigned int materialIndex_;
                glm::mat4 concatTransform_;
                std::string name_;
            };

            void loadModel(const std::string &path);

            void buildMeshEntry(aiNode *root, const aiScene *scene);

            void readNodePrepass(aiNode *node,
                                 const aiScene *scene,
                                 unsigned int &verticeBaseIndex,
                                 unsigned int &indiceBaseIndex,
                                 glm::mat4 const& concatMatrix);

            void readNode(aiNode *node,
                          const aiScene *scene,
                          std::vector<glm::vec3> &pos,
                          std::vector<glm::vec2> &tex,
                          std::vector<glm::vec3> &normal,
                          std::vector<glm::vec3> &tangent,
                          std::vector<glm::vec3> &bigent,
                          std::vector<unsigned int> &indices);

            void readMesh(aiMesh *mesh,
                          const aiScene *scene,
                          std::vector<glm::vec3> &pos,
                          std::vector<glm::vec2> &tex,
                          std::vector<glm::vec3> &normal,
                          std::vector<glm::vec3> &tangent,
                          std::vector<glm::vec3> &bigent,
                          std::vector<unsigned int> &indices);

            void readTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	
        private:
            //std::vector<BasicMeshEntry> m_Entries;
            // each mesh ---> material, numIndices,, baseIndex, baseVertex,materialIndex

            // material index ---> multiple textures and texture type
            // a same material index could be used by mesh in different nodes at any place in the scenegraph
            // a same material can have multiple textures. Texture have the path and type ?
            //std::unordered_multimap<unsigned int, std::unique_ptr<Texture>> materials;
            //materialId ---> vector of texture of path ---> Texture Object
            std::unordered_map<unsigned int, std::vector<Texture>> materials_;
            // path is unique
            std::unordered_map<std::string, std::unique_ptr<Texture>> textures_;
            // mesh name is unique ?? 
            std::unordered_map<std::string, MeshEntry> meshEntriesMap_;

            unsigned int numVertices_;
            unsigned int numIndices_;
            unsigned int numMeshes_;

            std::string directory_;
        };

    } // namespace Common
} // namespace OpenGLSandbox
