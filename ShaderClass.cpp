#include "ShaderClass.h"
#include <iostream>

// Helper function to compile the shader
bool ShaderClass::compileShader(const std::string& source, GLenum type) {
    shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    return checkCompilationErrors();
}

// Constructor that takes the path to the shader file and the type of shader
ShaderClass::ShaderClass(const std::string& path, GLenum type) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    if (!compileShader(source, type)) {
        std::cerr << "Shader compilation failed for: " << path << std::endl;
    }
}

// Default constructor
ShaderClass::ShaderClass() : shader(0) {}

// Destructor to clean up resources
ShaderClass::~ShaderClass() {
    if (shader != 0) {
        glDeleteShader(shader);
    }
}

// Method to get the shader ID
GLuint ShaderClass::getID() const {
    return shader;
}

// Method to find uniform location
GLint ShaderClass::findUniformLocation(const GLchar* name) const {
    return glGetUniformLocation(shader, name);
}

// Method to check and print shader compilation errors
bool ShaderClass::checkCompilationErrors() const {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: SHADER\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        return false;
    }
    return true;
}
