#pragma once

#include "include/glad/glad.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) asm("int3");
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall())

void GLClearError();

bool GLLogCall();

class Renderer
{
    private:

    public:
        void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
};
