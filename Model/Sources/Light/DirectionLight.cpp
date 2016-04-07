#include <Light/DirectionLight.hpp>
#include <Shader.hpp>


namespace Lighting
{
    DirectionLight::DirectionLight(const Ambient& ambient,      const AmbientLocation& ambientPath,
                                   const Diffuse& diffuse,      const DiffuseLocation& diffusePath,
                                   const Specular& specular,    const SpecularLocation& specularPath,
                                   const Direction& direction,  const DirectionLocation& directionPath)
    : Light(ambient, ambientPath, diffuse, diffusePath, specular, specularPath)
    , mDirection { direction }
    , mDirectionPath { directionPath }
    {}

    DirectionLight::~DirectionLight()
    {}

    // Initialize uniforms in shaders
    void DirectionLight::UseLight(Shader* shader) const
    {
        Light::UseLight(shader);
        glUniform3f(glGetUniformLocation(shader->getProgram(), mDirectionPath.directionLocation.c_str()),
                        mDirection.direction.x, mDirection.direction.y, mDirection.direction.z);
    }

}
