#include "glm/detail/type_mat.hpp"
#include "glm/detail/type_vec.hpp"
#include "include/glad/glad.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "GLFW/glfw3.h"
#include <GL/gl.h>
#include <algorithm>
#include <cstddef>
#include <string>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb/stb_image.h"

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(void)
{
    int width = 1280;
    int height = 720;

    GLFWwindow* window;

    if(!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "first opengl window", NULL, NULL);

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
        float vertexData[] = 
        {
            //front face
            -0.5f, -0.5f, -0.5f,      0.0f, 0.0f, //lower left corner
            0.5f, -0.5f, -0.5f,       1.0f, 0.0f, //lower right corner
            0.5f, 0.5f, -0.5f,        1.0f, 1.0f, //upper right corner 
            -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,  //upper left corner 

            //left face
            -0.5f, -0.5f, -0.5f,     0.0f, 0.0f, //lower left corner
            -0.5f, -0.5f, 0.5f,     1.0f, 0.0f, //lower right corner
            -0.5f, 0.5f, 0.5f,     1.0f, 1.0f, //upper right corner
            -0.5f, 0.5f, -0.5f,     0.0f, 1.0f, //upper left corner

            //right face 
            0.5f, -0.5f, 0.5f,     0.0f, 0.0f, //lower left corner
            0.5f, -0.5f, -0.5f,     1.0f, 0.0f, //lower right corner
            0.5f, 0.5f, -0.5f,      1.0f, 1.0f, //upper right corner
            0.5f, 0.5f, 0.5f,       0.0f, 1.0f, //upper left corner

            //back face
            0.5f, -0.5f, 0.5f,      0.0f, 0.0f, //lower left corner
            -0.5f, -0.5f, 0.5f,       1.0f, 0.0f, //lower right corner
            -0.5f, 0.5f, 0.5f,        1.0f, 1.0f, //upper right corner 
            0.5f, 0.5f, 0.5f,     0.0f, 1.0f,  //upper left corner 
            
            //top face
            -0.5, 0.5f, -0.5f,      0.0f, 0.0f, //lower left corner
            0.5f, 0.5f, -0.5f,      1.0f, 0.0f, //lower right corner
            0.5f, 0.5f, 0.5f,       1.0f, 1.0f, //upper right corner
            -0.5f, 0.5f, 0.5f,      0.0f, 1.0f, //upper left corner

            //bottom face
            -0.5f, -0.5f, -0.5f,     0.0f, 0.0f, //lower left corner
            0.5f, -0.5f, -0.5f,     1.0f, 0.0f, //lower right corner
            0.5f, -0.5f, 0.5f,      1.0f, 1.0f, //upper right corner
            -0.5f, -0.5f, 0.5f,     0.0f, 1.0f //upper left corner

        };

        unsigned int indices[] = 
        {
            0, 1, 2, 
            2, 3, 0,

            4, 5, 6, 
            6, 7, 4,

            8, 9, 10, 
            10, 11, 8,

            12, 13, 14,
            14, 15, 12,

            16, 17, 18, 
            18, 19, 16,

            20, 21, 22,
            22, 23, 20
        };
        
        
        VertexBufferLayout layout;

        VertexArray va;

        VertexBuffer vb(vertexData, 24 * 5 * sizeof(float));
        va.AddBuffer(vb, layout);

        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0));

        GLCall(glEnableVertexAttribArray(1));
        GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float))));

        IndexBuffer ib(indices, 36);

        Texture texture(std::string(RESOURCE_PATH) + "textures/container.jpg");

        Shader shader(std::string(RESOURCE_PATH) + "shaders/Basic.shader");

        shader.Bind();
        //shader.SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);
        //shader.SetUniform1i("texture", 0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 1000.0f);

        //glm::mat4 model = glm::mat4(1);
        glm::mat4 view = glm::mat4(1);
        //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        Renderer renderer;

        float r = 0.0f;
        float rincrement = 0.005f;

        GLCall(glEnable(GL_DEPTH_TEST));

        glm::vec3 cubePositions[] 
        {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.5f, 2.0f, -2.0f),
            glm::vec3(-1.5f, -1.0f, -2.0f)
        };

        glm::vec3 cubeRotations[]
        {
            glm::vec3(1.0f, 0.5f, 0.0f),
            glm::vec3(-0.5f, 1.0f, 0.5f),
            glm::vec3(-1.0f, 0.0f, -0.5f)
        };

        while(!glfwWindowShouldClose(window))
        {
            GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

            shader.Bind();
            //shader.SetUniform4f("u_Color", r, 0.5, 0.5, 1.0);

            shader.SetUniformMat4fv("view", view);
            shader.SetUniformMat4fv("projection", proj);

            glm::mat4 model;

            for(int i = 0; i < cubePositions->length(); i++)
            {
                model = glm::mat4(1.0);
                model = glm::translate(model, cubePositions[i]);
                model = glm::rotate(model, (float) glfwGetTime() * glm::radians(50.0f), cubeRotations[i]);
                
                shader.SetUniformMat4fv("model", model);
                renderer.Draw(va, ib, shader);
            }
            
            //shader.SetUniformMat4fv("model", model);
            //shader.SetUniformMat4fv("view", view);
            //shader.SetUniformMat4fv("projection", proj);

            //renderer.Draw(va, ib, shader);

            if(r > 1.0f)
            {
                rincrement = -0.005f;
            } 
            else if (r < 0.0f)
            {
                rincrement = 0.005f;
            }


            r += rincrement;

            //model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.5f, 1.0f, 0.0f));

            glfwSwapBuffers(window);

            glfwPollEvents();

            //this should keep it open right?
            //yes, yes it does
        }
    }

    glfwTerminate();

    return 0;
}