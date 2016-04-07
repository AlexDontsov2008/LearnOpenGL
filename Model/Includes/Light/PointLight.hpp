#ifndef _POINTLIGHT_HPP_
#define _POINTLIGHT_HPP_

#include <Light/GeomLight.hpp>
#include <Light/LightParameters.hpp>

namespace Lighting
{
    class PointLight : public GeomLight
    {
        public:
                        PointLight(const Ambient& ambient,      const AmbientLocation& ambientPath,
                                   const Diffuse& diffuse,      const DiffuseLocation& diffusePath,
                                   const Specular& specular,    const SpecularLocation& specularPath,
                                   const Position& position,    const PositionLocation& positionPath,
                                   const Constant& constant,    const ConstantLocation& constantPath,
                                   const Linear& linear,        const LinearLocation& linearPath,
                                   const Quadratic& quadratic,  const QuadraticLocation& quadraticPath);
            virtual     ~PointLight();

            // Initialize uniforms in shaders
            virtual void        UseLight(Shader* shader) const;
            // Return type of the light
            virtual LightType   GetLightType() const;
    };

    // Return type of the light
    inline Light::LightType PointLight::GetLightType() const
    {
        return Light::PointType;
    }
}


#endif // _POINTLIGHT_HPP_
