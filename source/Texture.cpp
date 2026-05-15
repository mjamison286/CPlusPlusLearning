#include "Texture.h"
#include "include/glad/glad.h"
#include "Renderer.h"

#include <iostream>

Texture::Texture(const std::string& filepath)
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load((const char*) &filepath, &width, &height, &nrChannels, 0);

    std::cout << "this is the data: " << data << std::endl;

    if(data)
    {
        std::cout << "loaded texture successfully" << std::endl;
        Texture::CreateTexture(data, width, height);
    }
    else 
    {
        std::cout << "failed to load texture" << std::endl;
        ASSERT(false);
    }


    stbi_image_free(data);
}

Texture::~Texture()
{

}

void Texture::Bind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, m_Texture));
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::CreateTexture(unsigned char* data, int width, int height)
{
    GLCall(glGenTextures(1, &m_Texture));

    Texture::Bind();
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));
}