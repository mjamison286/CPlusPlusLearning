#include "include/glad/glad.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

#include </usr/include/GLFW/glfw3.h>
#include <GL/gl.h>
#include <cstddef>


static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
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

        Shader shader("/mnt/DATA1/Coding/CPlusPlusLearning/source/resources/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float rincrement = 0.005f;

        while(!glfwWindowShouldClose(window))
        {
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.5, 0.5, 1.0);

            renderer.Draw(va, ib, shader);

            if(r > 1.0f)
            {
                rincrement = -0.005f;
            } 
            else if (r < 0.0f)
            {
                rincrement = 0.005f;
            }

            r += rincrement;

            glfwSwapBuffers(window);

            glfwPollEvents();

            //this should keep it open right?
            //yes, yes it does
        }
    }

    glfwTerminate();

    return 0;
}