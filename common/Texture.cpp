#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
// glew must be included before glfw
#include "Texture.h"

using namespace OpenGLSandbox::Common;

Texture::Texture(GLenum textureTarget, const std::string &path, const std::string &type) : textureTarget_(textureTarget), path_(path), type_(type)
{
    load();
}

void Texture::load()
{
    int width, height, nrComponents;
    unsigned char *data;
    GLenum format;

    try
    {
        data = stbi_load(path_.c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glGenTextures(1, &textureObj_);
            glBindTexture(textureTarget_, textureObj_);
            glTexImage2D(textureTarget_, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            // support all kinds of texture type
            glGenerateMipmap(textureTarget_);
            glTexParameterf(textureTarget_, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameterf(textureTarget_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path_ << std::endl;
        }
        stbi_image_free(data);
    }
    catch (std::exception &e)
    {
        std::cout << "Error loading texture '" << path_ << "': " << e.what() << std::endl;
        stbi_image_free(data);
    }
}

void Texture::bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(textureTarget_, textureObj_);
}
