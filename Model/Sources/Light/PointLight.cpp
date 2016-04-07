#include <Light/PointLight.hpp>

namespace Lighting
{

    PointLight::PointLight(const Ambient& ambient,      const AmbientLocation& ambientPath,
                           const Diffuse& diffuse,      const DiffuseLocation& diffusePath,
                           const Specular& specular,    const SpecularLocation& specularPath,
                           const Position& position,    const PositionLocation& positionPath,
                           const Constant& constant,    const ConstantLocation& constantPath,
                           const Linear& linear,        const LinearLocation& linearPath,
                           const Quadratic& quadratic,  const QuadraticLocation& quadraticPath)
    : GeomLight { ambient,      ambientPath,
                  diffuse,      diffusePath,
                  specular,     specularPath,
                  position,     positionPath,
                  constant,     constantPath,
                  linear,       linearPath,
                  quadratic,    quadraticPath }
    {}

    PointLight::~PointLight()
    {}

    // Initialize uniforms in shaders
    void PointLight::UseLight(Shader* shader) const
    {
        GeomLight::UseLight(shader);
    }

}
