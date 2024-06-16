#ifndef PROGRAM_H
#define PROGRAM_H

#include "ShaderClass.h"
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Program {
private:
    GLuint prog;          // Program ID
    ShaderClass vert;     // Vertex shader
    ShaderClass frag;     // Fragment shader

    void create();        // Helper function to create the shader program

public:
    // Constructor that takes paths to the vertex and fragment shader files
    Program(const std::string& v_path, const std::string& f_path);
    
    // Constructor that takes ShaderClass objects for vertex and fragment shaders
    Program(const ShaderClass& vert, const ShaderClass& frag);
    
    // Destructor to clean up resources
    ~Program();
    
    // Method to use the shader program
    void use() const;
    
    // Getter for the fragment shader ID
    unsigned int getFrag() const;
    
    // Getter for the vertex shader ID
    unsigned int getVert() const;
    
    // Method to get the program ID
    GLuint getID() const;

    // Method to check and print shader program linking errors
    bool checkLinkingErrors() const;
};

#endif // PROGRAM_H
