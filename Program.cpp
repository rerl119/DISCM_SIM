#include "Program.h"
#include <iostream>

// Helper function to create the shader program
void Program::create() {
    prog = glCreateProgram();
    glAttachShader(prog, vert.getID());
    glAttachShader(prog, frag.getID());
    glLinkProgram(prog);

    if (!checkLinkingErrors()) {
        std::cerr << "Shader program linking failed!" << std::endl;
    }
}

// Constructor that takes paths to the vertex and fragment shader files
Program::Program(const std::string& v_path, const std::string& f_path)
    : vert(v_path, GL_VERTEX_SHADER), frag(f_path, GL_FRAGMENT_SHADER) {
    create();
}

// Constructor that takes ShaderClass objects for vertex and fragment shaders
Program::Program(const ShaderClass& vertShader, const ShaderClass& fragShader)
    : vert(vertShader), frag(fragShader) {
    create();
}

// Destructor to clean up resources
Program::~Program() {
    glDeleteProgram(prog);
}

// Method to use the shader program
void Program::use() const {
    glUseProgram(prog);
}

// Getter for the fragment shader ID
unsigned int Program::getFrag() const {
    return frag.getID();
}

// Getter for the vertex shader ID
unsigned int Program::getVert() const {
    return vert.getID();
}

// Method to get the program ID
GLuint Program::getID() const {
    return prog;
}

// Method to check and print shader program linking errors
bool Program::checkLinkingErrors() const {
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(prog, 1024, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: PROGRAM\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        return false;
    }
    return true;
}
