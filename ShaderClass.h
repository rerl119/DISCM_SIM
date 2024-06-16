#ifndef SHADERCLASS_H
#define SHADERCLASS_H

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>

class ShaderClass {
private:
    GLuint shader; // Shader ID

    // Helper function to compile the shader
    bool compileShader(const std::string& source, GLenum type);

public:
    // Constructor that takes the path to the shader file and the type of shader
    ShaderClass(const std::string& path, GLenum type);

    // Default constructor
    ShaderClass();

    // Destructor to clean up resources
    ~ShaderClass();

    // Method to get the shader ID
    GLuint getID() const;

    // Method to find uniform location
    GLint findUniformLocation(const GLchar* name) const;

    // Method to check and print shader compilation errors
    bool checkCompilationErrors() const;
};

#endif // SHADERCLASS_H
