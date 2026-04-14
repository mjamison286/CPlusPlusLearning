#include "include/glad/glad.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include </usr/include/GLFW/glfw3.h>
#include <GL/gl.h>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>



static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int) type] << line << "\n";
        }
    }

    return{ss[0].str(), ss[1].str()};
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "failed to compile " << (type == GL_VERTEX_SHADER ? "vertexShader" : "fragmentShader") << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);

        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    if(!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "first opengl window", NULL, NULL);

    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGL();

    glfwSetKeyCallback(window, keyCallback);

    glfwShowWindow(window);
    {
        float positions[] = 
        {
            -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 
            -0.5f, 0.5f
            
        };

        unsigned int indices[] = 
        {
            0, 1, 2, 
            2, 3, 0
        };

        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

        IndexBuffer ib(indices, 6);

        ShaderProgramSource source = ParseShader("/mnt/DATA1/Coding/CPlusPlusLearning/source/resources/shaders/Basic.shader");

        unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        GLCall(glUseProgram(shader));

        GLCall(int location = glGetUniformLocation(shader, "u_Color"));
        ASSERT(location != -1);
        GLCall(glUniform4f(location, 0.0f, 0.0f, 1.0f, 1.0f));

        GLCall(glBindVertexArray(0));
        GLCall(glUseProgram(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        float r = 0.0f;
        float rincrement = 0.005f;

        float g = 0.25f;
        float gincrement = 0.01f;

        float b = 0.10f;
        float bincrement = 0.0025f;

        while(!glfwWindowShouldClose(window))
        {
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            GLCall(glUseProgram(shader));
            GLCall(glUniform4f(location, r, g, b, 1.0));

            va.Bind();
            ib.Bind();

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            if(r > 1.0f)
            {
                rincrement = -0.005f;
            } 
            else if (r < 0.0f)
            {
                rincrement = 0.005f;
            }

            if(g > 1.0f)
            {
                gincrement = -0.01f;
            }
            else if (g < 0.0f)
            {
                gincrement = 0.01f;
            }

            if(b > 1.0f)
            {
                bincrement = -0.0025f;
            }
            else if (b < 0.0f)
            {
                bincrement = 0.0025f;
            }

            r += rincrement;
            g += gincrement;
            b += bincrement;

            glfwSwapBuffers(window);

            glfwPollEvents();

            //this should keep it open right?
            //yes, yes it does
        }

        GLCall(glDeleteProgram(shader));
    }

    glfwTerminate();

    return 0;
}