#ifndef _SPOTLIGHT_HPP_
#define _SPOTLIGHT_HPP_

#include <Light/GeomLight.hpp>
#include <Light/LightParameters.hpp>

namespace Lighting
{
    class SpotLight : public GeomLight
    {
        public:
                             SpotLight(const Ambient& ambient,          const AmbientLocation& ambientPath,
                                       const Diffuse& diffuse,          const DiffuseLocation& diffusePath,
                                       const Specular& specular,        const SpecularLocation& specularPath,
                                       const Position& position,        const PositionLocation& positionPath,
                                       const Constant& constant,        const ConstantLocation& constantPath,
                                       const Linear& linear,            const LinearLocation& linearPath,
                                       const Quadratic& quadratic,      const QuadraticLocation& quadraticPath,
                                       const Direction& direction,      const DirectionLocation& directionPath,
                                       const CutOff& cutOff,            const CutOffLocation& cutOffPath,
                                       const OuterCutOff& outerCutOff,  const OuterCutOffLocation& outerCutOffPath);
                virtual     ~SpotLight();

                // GET & SET direction value
                const Direction&    GetDirection() const;
                void                SetDirection(const Direction& direction);



                // Initialize uniforms in shaders
                virtual void        UseLight(Shader* shader) const;
                // Return type of the light
                virtual LightType   GetLightType() const;

            private:
                Direction           mDirection;
                DirectionLocation   mDirectionPath;

                CutOff              mCutOff;
                CutOffLocation      mCutOffPath;

                OuterCutOff         mOuterCutOff;
                OuterCutOffLocation mOuterCutOffPath;
    };

    // GET & SET direction value
    inline const Direction& SpotLight::GetDirection() const
    {
        return mDirection;
    }

    inline void SpotLight::SetDirection(const Direction& direction)
    {
        mDirection = direction;
    }

    // Return type of the light
    inline Light::LightType SpotLight::GetLightType() const
    {
        return Light::SpotType;
    }
}

#endif // _SPOTLIGHT_HPP_
