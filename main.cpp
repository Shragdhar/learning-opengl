#include <cstddef>
#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

const char* AfragmentShaderCode = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.3f, 0.6f, 1.0f);\n"
    "}\n\0";

const char* BfragmentShaderCode = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

const char* vertexShaderCode = "#version 330 core\n"
                            "layout (location = 0) in vec4 apos;\n"
                            "void main()\n"
                            "{\n"
                            "   gl_Position = vec4(apos.x, apos.y, apos.z, 1);\n"
                            "}\0";

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
    

    unsigned int AfragmentShader{0};
    AfragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(AfragmentShader, 1, &AfragmentShaderCode, NULL);
    glCompileShader(AfragmentShader);

    unsigned int BfragmentShader{0};
    BfragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(BfragmentShader, 1, &BfragmentShaderCode, NULL);
    glCompileShader(BfragmentShader);

    unsigned int vertexShader{0};
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    
    unsigned int AshaderProgram{0};
    AshaderProgram = glCreateProgram();
    glAttachShader(AshaderProgram, vertexShader);
    glAttachShader(AshaderProgram, AfragmentShader);
    glLinkProgram(AshaderProgram);
   
    unsigned int BshaderProgram{0};
    BshaderProgram = glCreateProgram();
    glAttachShader(BshaderProgram, vertexShader);
    glAttachShader(BshaderProgram, BfragmentShader);
    glLinkProgram(BshaderProgram);

    //Destroy Shaders that are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(AfragmentShader);
    glDeleteShader(BfragmentShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    glGetProgramiv(AshaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(AshaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER:PROGRAM:FAILED\n" << infoLog << std::endl;
    }

    //The vertices of the triangle we want to create, no z component = no 3D
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, //bottom left
         0.5f, -0.5f, 0.0f, //bottom right
        -0.5f,  0.5f, 0.0f, //top left
         0.5f,  0.5f, 0.0f, //top right
    };
    
    unsigned int indices1[] = {
        0, 2, 3, //first triangle    
    };
    
    unsigned int indices2[] = {
        0, 1, 3, //first triangle    
    };
    
    unsigned int EBOid1{0}, EBOid2{0};
    unsigned int VAOid1{0}, VAOid2{0};
    
    unsigned int VBO{0};
     
    glGenVertexArrays(1, &VAOid1);
    glGenVertexArrays(1, &VAOid2);
    glGenBuffers(1, &VBO);  //Generating buffer where our data will be stored in memory
    glGenBuffers(1, &EBOid1);
    glGenBuffers(1, &EBOid2);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    
    glBindVertexArray(VAOid1);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOid1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
    
    
    glBindVertexArray(VAOid2);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOid2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
    
    
    

    while(!glfwWindowShouldClose(window))
    {
        ProcessInput(window);
        
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
 
        glUseProgram(AshaderProgram);
        glBindVertexArray(VAOid1);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        glUseProgram(BshaderProgram);
        glBindVertexArray(VAOid2);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    
    glfwTerminate();
    return 0;
}
