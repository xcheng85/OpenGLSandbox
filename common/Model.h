#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include <GLFW/glfw3.h>
#include <assimp/scene.h>

#include "Texture.h"

namespace OpenGLSandbox
{
    namespace Common
    {
        class Texture;
        class Model
        {
        public:
            Model(const std::string &path);
            virtual ~Model();
            void draw(GLuint shaderProgram);

        protected:
        /*
            struct BasicMeshEntry
            {
                BasicMeshEntry()
                {
                    NumIndices = 0;
                    BaseVertex = 0;
                    BaseIndex = 0;
                    MaterialIndex = INVALID_MATERIAL;
                }

                unsigned int NumIndices;
                unsigned int BaseVertex;
                unsigned int BaseIndex;
                unsigned int MaterialIndex;
            };*/

            void loadModel(const std::string &path);
            void processNode(aiNode *node, const aiScene *scene);

            // numVertice
            // numIndices
            // numMeshes
            // numMaterial
            // transformation matrix
            void preScan(aiNode *node, const aiScene *scene);

        private:
            //std::vector<BasicMeshEntry> m_Entries;
            // material index ---> multiple textures and texture type
            // a same material index could be used by mesh in different nodes at any place in the scenegraph
            // a same material can have multiple textures. Texture have the path and type ? 
            //std::unordered_multimap<unsigned int, std::unique_ptr<Texture>> materials; 
            std::unordered_map<std::string, std::unique_ptr<Texture>> textures_;

            //string directory;
        };

    } // namespace Common
} // namespace OpenGLSandbox
