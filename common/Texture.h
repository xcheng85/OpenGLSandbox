#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace OpenGLSandbox
{
    namespace Common
    {
        class Texture
        {
        public:
            // 1d/2d/3d/textureArray
            Texture(GLenum textureTarget, const std::string &path, const std::string &type);
            virtual ~Texture(){};
            void load();

            void bind(GLenum textureUnit);

            const auto &getPath() const { return path_; };
            const auto &getType() const { return type_; };
            const auto &getTextureObj() const { return textureObj_; };
            const auto &getTextureTarget() const { return textureTarget_; };

        private:
            std::string path_;
            std::string type_; // "texture_diffuse", etc.
            GLenum textureTarget_;
            GLuint textureObj_;
        };
    } // namespace Common
} // namespace OpenGLSandbox
