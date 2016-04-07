#include <Light/GeomLight.hpp>
#include <Shader.hpp>

namespace Lighting
{
    GeomLight::GeomLight(const Ambient& ambient,      const AmbientLocation& ambientPath,
                         const Diffuse& diffuse,      const DiffuseLocation& diffusePath,
                         const Specular& specular,    const SpecularLocation& specularPath,
                         const Position& position,    const PositionLocation& positionPath,
                         const Constant& constant,    const ConstantLocation& constantPath,
                         const Linear& linear,        const LinearLocation& linearPath,
                         const Quadratic& quadratic,  const QuadraticLocation& quadraticPath)
    : Light { ambient, ambientPath, diffuse, diffusePath, specular, specularPath }
    , mPosition { position }
    , mPositionPath { positionPath }
    , mConstant { constant }
    , mConstantPath { constantPath }
    , mLinear { linear }
    , mLinearPath { linearPath }
    , mQuadratic { quadratic }
    , mQuadraticPath { quadraticPath }
    {}

    GeomLight::~GeomLight()
    {}

    // Initialize uniforms in shaders
    void GeomLight::UseLight(Shader* shader) const
    {
        Light::UseLight(shader);


        glUniform3f(glGetUniformLocation(shader->getProgram(), mPositionPath.positionLocation.c_str()),
                                mPosition.position.x, mPosition.position.y, mPosition.position.z);
        glUniform1f(glGetUniformLocation(shader->getProgram(), mConstantPath.constantLocation.c_str()), mConstant.constant);
        glUniform1f(glGetUniformLocation(shader->getProgram(), mLinearPath.linearLocation.c_str()), mLinear.linear);
        glUniform1f(glGetUniformLocation(shader->getProgram(), mQuadraticPath.quadraticLocation.c_str()), mQuadratic.quadratic);
    }
}
