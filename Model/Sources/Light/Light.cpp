#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Light/Light.hpp>
#include <Shader.hpp>


namespace Lighting
{
    Light::Light(const Ambient& ambient, const AmbientLocation& ambientPath,
                 const Diffuse& diffuse, const DiffuseLocation& diffusePath,
                 const Specular& specular, const SpecularLocation& specularPath)
    : mAmbientVal { ambient }
    , mAmbientPath { ambientPath }
    , mDiffuseVal { diffuse }
    , mDiffusePath { diffusePath }
    , mSpecularVal { specular }
    , mSpecularPath { specularPath }
    {}


    Light::~Light()
    {}

    // Initialize uniforms in shaders
    void Light::UseLight(Shader* shader) const
    {
        if (shader != nullptr)
        {
            // Get location and initialize by our values
            glUniform3f(glGetUniformLocation(shader->getProgram(), mAmbientPath.ambientLocation.c_str()),
                        mAmbientVal.ambient.x, mAmbientVal.ambient.y, mAmbientVal.ambient.z);

            glUniform3f(glGetUniformLocation(shader->getProgram(), mDiffusePath.diffuseLocation.c_str()),
                        mDiffuseVal.diffuse.x, mDiffuseVal.diffuse.y, mDiffuseVal.diffuse.z);

            glUniform3f(glGetUniformLocation(shader->getProgram(), mSpecularPath.specularLocation.c_str()),
                        mSpecularVal.specular.x,  mSpecularVal.specular.y,  mSpecularVal.specular.z);
        }
        else
        {
            throw std::logic_error("IN::FUNCTION::UseLight(Shader*)::SHADER::UNDEFINED");
        }
    }

}























