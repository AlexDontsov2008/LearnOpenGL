#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
    public:
        // Constructors reads and builds the shader
                Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
                Shader();

        // Use the program
        void    Use();

        // Get program
        GLuint  getProgram() const;

        // Update shader program from the new shaders
        void    setNewShaders(const GLchar* vertexPath, const GLchar* fragmentPath);

    private:
        // Create shader from  shader code
        GLuint  createShader(const GLchar* shaderCode, GLenum shaderType) const;

    private:
        // The program ID
        GLuint  mProgram;
};

// Get program
inline GLuint Shader::getProgram() const
{
    return mProgram;
}

#endif // _SHADER_HPP_
