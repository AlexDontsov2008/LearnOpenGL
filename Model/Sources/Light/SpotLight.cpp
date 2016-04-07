#include <Light/SpotLight.hpp>
#include <Shader.hpp>

namespace Lighting
{

    SpotLight::SpotLight(const Ambient& ambient,          const AmbientLocation& ambientPath,
                         const Diffuse& diffuse,          const DiffuseLocation& diffusePath,
                         const Specular& specular,        const SpecularLocation& specularPath,
                         const Position& position,        const PositionLocation& positionPath,
                         const Constant& constant,        const ConstantLocation& constantPath,
                         const Linear& linear,            const LinearLocation& linearPath,
                         const Quadratic& quadratic,      const QuadraticLocation& quadraticPath,
                         const Direction& direction,      const DirectionLocation& directionPath,
                         const CutOff& cutOff,            const CutOffLocation& cutOffPath,
                         const OuterCutOff& outerCutOff,  const OuterCutOffLocation& outerCutOffPath)
    : GeomLight { ambient,      ambientPath,
                  diffuse,      diffusePath,
                  specular,     specularPath,
                  position,     positionPath,
                  constant,     constantPath,
                  linear,       linearPath,
                  quadratic,    quadraticPath }
    , mDirection { direction }
    , mDirectionPath { directionPath }
    , mCutOff { cutOff }
    , mCutOffPath { cutOffPath }
    , mOuterCutOff { outerCutOff }
    , mOuterCutOffPath { outerCutOffPath }
    {}

    SpotLight::~SpotLight()
    {}

    // Initialize uniforms in shaders
    void SpotLight::UseLight(Shader* shader) const
    {
        GeomLight::UseLight(shader);

        glUniform3f(glGetUniformLocation(shader->getProgram(), mDirectionPath.directionLocation.c_str()),
                                         mDirection.direction.x, mDirection.direction.y, mDirection.direction.z);
        glUniform1f(glGetUniformLocation(shader->getProgram(), mCutOffPath.cutOffLocation.c_str()), mCutOff.cutOff);
        glUniform1f(glGetUniformLocation(shader->getProgram(), mOuterCutOffPath.outerCutOffLocation.c_str()),
                                         mOuterCutOff.outerCutOff);

    }
}
