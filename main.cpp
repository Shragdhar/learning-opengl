#include <cstddef>
#include <cmath>
#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"

//Defining Callbacks
void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    glfwSetErrorCallback(error_callback);
    
    glfwInit(); //Initialize GLFW

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create a GLFW window where the graphics take place
    GLFWwindow* window = glfwCreateWindow(800, 600, "opengl bro", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to initialise GLFW window! " << '\n';

        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    } 
    
    //Set the viewport where all the visuals take place inside of the window
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   
    Shader shader1("/home/q/Development/C++/OpenGL/opengl-first-proj/shaders/vertexShader.txt", "/home/q/Development/C++/OpenGL/opengl-first-proj/shaders/fragmentShader.txt");
    
    //The vertices of the triangle we want to create, no z component = no 3D
    float vertices[] = {
        //vertices          //colors
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //bottom left
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,//bottom right
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f//top left
    };
    
    unsigned int indices1[] = {
        0, 1, 2 //first triangle    
    };
   
    unsigned int EBOid1{0}, VAOid1{0};
    unsigned int VBO{0};
    
    glGenVertexArrays(1, &VAOid1);
    glGenBuffers(1, &VBO);  //Generating buffer where our data will be stored in memory
    glGenBuffers(1, &EBOid1);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(VAOid1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOid1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
    
    while(!glfwWindowShouldClose(window))
    {
        ProcessInput(window);
        
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
       
        shader1.use();
         
        glBindVertexArray(VAOid1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}
