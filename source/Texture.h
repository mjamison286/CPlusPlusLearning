#pragma once

#include <string>
#include "include/stb/stb_image.h"

class Texture
{
public:
    Texture(const std::string& filepath);
    ~Texture();
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned int m_Texture;

    void CreateTexture(unsigned char* data, int width, int height);
    void Bind() const;
    void Unbind() const;
};