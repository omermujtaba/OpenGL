#include <iostream>

//GLEW = GL Extension Wrangler

#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

//Shader
#include "Shader.h"

// Window Deimensions
const GLint HEIGHT=800, WIDTH = 600;

int main(){
    
    // Initialize GLFW
    glfwInit();
    
    // Set all required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    //Create GLFWindow for all GLFW functions
    GLFWwindow *window = glfwCreateWindow(WIDTH,HEIGHT,"Learn GL", nullptr,nullptr);
    
    int screenWidth,screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    // Return if GLFW window failed to create
    if(nullptr == window){
        std:: cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return  -1;
    }
    
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    
    // Iniitalize GLEW
    if(GLEW_OK != glewInit()){
        std:: cout << "Failed to init GLEW" << std::endl;
        return -1;
    }
    
    glViewport(0, 0, screenWidth, screenHeight);
    
    
    
    GLfloat vertices[] =
    {
        //position          //color
        -0.5f, -0.5, 0.0f,  1.0f, 0.0f,0.0f,    //bottom left
        0.5f, -0.5, 0.0f,   0.0f, 1.0f,0.0f,    //bottom right
        0.0f, 0.5, 0.0f,    0.0f, 0.0f,1.0f    //top middle
    };
    
    GLuint VBO, VAO;
    glGenVertexArrays(  1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3, GL_FLOAT, GL_TRUE,3 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    
    
    
    //Game Loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate();
    return 0;
    
    
}



