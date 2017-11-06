#include <iostream>

//GLEW = GL Extension Wrangler

#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

// Window Deimensions
const GLint HEIGHT=800, WIDTH = 600;

const GLchar *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 postion;\n"
"void main()\n"
"{\n"
"gl_position = vec4 (position.x, position.y, position.z,1.0);\n"
"}";

const GLchar *fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4 (1.0f,0.5f,0.2f, 1.0f );\n"
"}";

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
    
    // Create shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    GLint success;
    GLchar infoLog[512];
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    // If shader failed
    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std:: cout << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        
    }
    
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
    
    
}


