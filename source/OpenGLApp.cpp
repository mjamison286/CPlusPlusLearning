#define GLEW_STATIC
#include </usr/include/GL/glew.h>
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

    window = glfwCreateWindow(640, 480, "first opengl window", NULL, NULL);

    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallback);

    glfwShowWindow(window);

    //GLenum err = glewInit();

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        int width, height;

        glfwGetFramebufferSize(window, &width, &height);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        glfwSwapBuffers(window);

        glfwPollEvents();

        //this should keep it open right?
    }

    return 0;
}

