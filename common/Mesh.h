#pragma once

#include <string>

#include <vector>

#include <GL/glew.h>

#include <glm/vec2.hpp> // vec2, bvec2, dvec2, ivec2 and uvec2
#include <glm/vec3.hpp> // vec3, bvec3, dvec3, ivec3 and uvec3
#include <glm/vec4.hpp> // vec4, bvec4, dvec4, ivec4 and uvec4

#include "Texture.h"

namespace OpenGLSandbox
{
    namespace Common
    {
        struct Vertex
        {
            glm::vec3 pos_;
            glm::vec2 tex_;
            glm::vec3 normal_;
            glm::vec3 tangent_;
            glm::vec3 bigent_;
        };

        class Mesh
        {
        public:
            // SubMesh did not own the vao, model owns the vao, performance consideration
            // vao defines the struct of vertex inputs, tightly depends on the graphics algorithm
            // textures, material related to this mesh.

            Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture *> &&textures,
                 GLuint vao,
                 unsigned int baseVertex,
                 unsigned int baseIndex);

            void load();

            void draw();

        private:
            std::vector<Vertex> vertices_;
            std::vector<unsigned int> indices;
            std::vector<Texture *> textures;
            GLuint vao_;
            unsigned int baseVertex_;
            unsigned int baseIndex_;

            //unsigned int materialIndex_;
            // m_Entries[i].MaterialIndex = pScene->mMeshes[i]->mMaterialIndex;
            // m_Entries[i].NumIndices = pScene->mMeshes[i]->mNumFaces * 3;
            //m_Entries[i].BaseVertex = NumVertices;
            //m_Entries[i].BaseIndex = NumIndices;
        };
    } // namespace Common
} // namespace OpenGLSandbox