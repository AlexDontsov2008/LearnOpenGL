#ifndef _DIRECTIONLIGHT_HPP_
#define _DIRECTIONLIGHT_HPP_

#include <Light/Light.hpp>
#include <Light/LightParameters.hpp>

namespace Lighting
{
    class DirectionLight : public Light
    {
        public:
                        DirectionLight(const Ambient& ambient,      const AmbientLocation& ambientPath,
                                       const Diffuse& diffuse,      const DiffuseLocation& diffusePath,
                                       const Specular& specular,    const SpecularLocation& specularPath,
                                       const Direction& direction,  const DirectionLocation& directionPath);
            virtual     ~DirectionLight();


            // GET & SET direction value
            const Direction&    GetDirection() const;
            void                SetDirection(const Direction& direction);

            // SET direction path value
            void                SetDirectionLocation(const DirectionLocation& directionPath);

            // Initialize uniforms in shaders
            virtual void    UseLight(Shader* shader) const;
            // Return type of the light
            virtual LightType   GetLightType() const;


        private:
            Direction           mDirection;
            DirectionLocation   mDirectionPath;
    };


    // GET & SET direction value
    inline const Direction& DirectionLight::GetDirection() const
    {
        return mDirection;
    }

    inline void DirectionLight::SetDirection(const Direction& direction)
    {
        mDirection = direction;
    }

    // SET direction path value
    inline void DirectionLight::SetDirectionLocation(const DirectionLocation& directionPath)
    {
        mDirectionPath = directionPath;
    }

    inline Light::LightType DirectionLight::GetLightType() const
    {
        return DirectionType;
    }

}

#endif // _DIRECTIONLIGHT_HPP_
