#ifndef _GEOMLIGHT_HPP_
#define _GEOMLIGHT_HPP_

#include <Light/Light.hpp>
#include <Light/LightParameters.hpp>

namespace Lighting
{
    class GeomLight : public Light
    {
        public:
                         GeomLight(const Ambient& ambient,      const AmbientLocation& ambientPath,
                                   const Diffuse& diffuse,      const DiffuseLocation& diffusePath,
                                   const Specular& specular,    const SpecularLocation& specularPath,
                                   const Position& position,    const PositionLocation& positionPath,
                                   const Constant& constant,    const ConstantLocation& constantPath,
                                   const Linear& linear,        const LinearLocation& linearPath,
                                   const Quadratic& quadratic,  const QuadraticLocation& quadraticPath);
            virtual     ~GeomLight() = 0;


            // GET & SET position, const, linear, quadratic
            const Position&     GetPosition() const;
            void                SetPosition(const Position& position);

            const Constant&     GetConstant() const;
            void                SetConstant(const Constant& constant);

            const Linear&       GetLinear() const;
            void                SetLinear(const Linear& linear);

            const Quadratic&    GetQuadratic() const;
            void                SetQuadratic(const Quadratic& quadratic);

            // Initialize uniforms in shaders
            virtual void    UseLight(Shader* shader) const = 0;
            // Return type of the light
            virtual LightType   GetLightType() const;


        private:
            Position            mPosition;
            PositionLocation    mPositionPath;

            Constant            mConstant;
            ConstantLocation    mConstantPath;

            Linear              mLinear;
            LinearLocation      mLinearPath;

            Quadratic           mQuadratic;
            QuadraticLocation   mQuadraticPath;
    };

    // GET & SET position, const, linear, quadratic
    inline const Position& GeomLight::GetPosition() const
    {
        return mPosition;
    }

    inline void GeomLight::SetPosition(const Position& position)
    {
        mPosition = position;
    }

    inline const Constant& GeomLight::GetConstant() const
    {
        return mConstant;
    }

    inline void  GeomLight::SetConstant(const Constant& constant)
    {
        mConstant = constant;
    }

    inline const Linear& GeomLight::GetLinear() const
    {
        return mLinear;
    }

    inline void GeomLight::SetLinear(const Linear& linear)
    {
        mLinear = linear;
    }

    inline const Quadratic& GeomLight::GetQuadratic() const
    {
        return mQuadratic;
    }

    inline void GeomLight::SetQuadratic(const Quadratic& quadratic)
    {
        mQuadratic = quadratic;
    }

    inline Light::LightType GeomLight::GetLightType() const
    {
        return Light::GeomType;
    }
}

#endif // _GEOMLIGHT_HPP_
