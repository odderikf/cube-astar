//OpenGL
#ifndef CALLBACK
#if defined(_ARM_)
#define CALLBACK
#else
#define CALLBACK __stdcall
#endif
#endif
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

//dependencies
#include <iostream>
#include <sstream>

//own files
#include "astar_s.hpp"
#include "graph.hpp"
#include "mylib/heap.hpp"
#include "cube.h"

std::string centiseconds_to_HHmmssss(unsigned long cs){
    unsigned long hours = cs / 360000;
    cs %= 360000;
    unsigned long minutes = cs / 6000;
    cs %= 6000;
    unsigned long seconds = cs / 100;
    cs %= 100;
    unsigned long centiseconds = cs;

    std::ostringstream s;
    s << hours << ":" << minutes << ":" << seconds << "." << centiseconds;
    return s.str();
}

float vertices[] = {
        0.f, 0.f, -5.f,
        4.f, 0.f, -5.f,
        0.f, 4.f, -5.f,
        4.f, 4.f, -5.f
};

// Shader sources
const GLchar* vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    void main()
    {
        gl_Position = ftransform();
    }
)glsl";
const GLchar* fragmentSource = R"glsl(
    #version 150 core
    out vec4 outColor;
    uniform vec3 triangleColor;
    void main()
    {
        outColor = vec4(1, 1,1,1);
    }
)glsl";

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(){

    if (!glfwInit()){
        std::cout << "initialization failed" << std::endl;
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(1600, 900, "cube", nullptr, nullptr);

    if(!window){
        glfwTerminate();
        std::cout << "could not create window" << std::endl;
        return EXIT_FAILURE;
    }

    if (!glewInit()){
        std::cout << "glew init failed" << std::endl;
        return EXIT_FAILURE;
    }


    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLuint posAttrib = static_cast<GLuint>(glGetAttribLocation(shaderProgram, "position"));
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(posAttrib);

    glfwSetKeyCallback(window, key_callback);

    threebythree cube;

    while (!glfwWindowShouldClose(window)){

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::cout << glGetError() << std::endl;
    glfwTerminate();
    return EXIT_SUCCESS;
}
