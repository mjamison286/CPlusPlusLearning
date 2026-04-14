#pragma once

#include "include/glad/glad.h"

#define ASSERT(x) if(!(x)) asm("int3");
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall())

void GLClearError();

bool GLLogCall();
