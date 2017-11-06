#include <iostream>

//GLEW = GL Extension Wrangler

#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

// Window Deimensions
const GLint HEIGHT=800, WIDTH = 600;

const GLchar *vertexShaderSource = "#version 330 core\n"
"layout ( location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4 (position.x, position.y, position.z, 1.0);\n"
"}\0";

const GLchar *fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4 (1.0f,0.5f,0.2f, 1.0f );\n"
"}\0"; // vec4(Red,Green,Blue,Alpha);


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
    
    // If vertex shader failed
    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std:: cout << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    GLuint framgmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(framgmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(framgmentShader);
    
    glGetShaderiv(framgmentShader, GL_COMPILE_STATUS, &success);
    
    // If fragment shader failed
    if(!success){
        glGetShaderInfoLog(framgmentShader,512,NULL,infoLog);
        std:: cout << "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        
    }
    
    GLuint shaderProgram = glCreateProgram();
    glAttachShader( shaderProgram , vertexShader);
    glAttachShader (shaderProgram , framgmentShader);
    glLinkProgram( shaderProgram);
    
    glGetShaderiv( shaderProgram, GL_LINK_STATUS , &success);
    
    // if Shader program failed
    if(!success){
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        std:: cout << "ERROR::FRAGMENT::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    
    glDeleteShader(vertexShader);
    glDeleteShader(framgmentShader);
    
    GLfloat vertices[] =
    {
        -0.5f, -0.5, 0.0f, //bottom left
        0.5f, -0.5, 0.0f, //bottom right
        0.0f, 0.5, 0.0f //top middle
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



