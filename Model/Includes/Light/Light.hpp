#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Uncopyable.hpp>
#include <Light/LightParameters.hpp>

class Shader;

namespace Lighting
{
    class Light
    {
        public:
            enum LightType
            {
                DirectionType,
                GeomType,
                PointType,
                SpotType
            };


        public:
                                Light(const Ambient& ambient, const AmbientLocation& ambientPath,
                                      const Diffuse& diffuse, const DiffuseLocation& diffusePath,
                                      const Specular& specular, const SpecularLocation& specularPath);

            virtual         ~Light() = 0;


            // Get & Set for Ambient, Diffuse, Specular components
            const Ambient&      GetAmbient() const;
            const Diffuse&      GetDiffuse() const;
            const Specular&     GetSpecular() const;

            void                SetAmbient(const Ambient& ambient);
            void                SetDiffuse(const Diffuse& diffuse);
            void                SetSpecular(const Specular& specular);


            // Set for Ambient, Diffuse, Specular locations
            void                SetAmbientLocation(const AmbientLocation& ambientPath);
            void                SetDiffuseLocation(const DiffuseLocation& diffusePath);
            void                setSpecularLocation(const SpecularLocation& specularPath);


            // Initialize uniforms in shaders
            virtual void        UseLight(Shader* shader) const = 0;
            // Return type of the light
            virtual LightType   GetLightType() const = 0;


        private:
            // Light components values and locations
            Ambient             mAmbientVal;
            AmbientLocation     mAmbientPath;
            Diffuse             mDiffuseVal;
            DiffuseLocation     mDiffusePath;
            Specular            mSpecularVal;
            SpecularLocation    mSpecularPath;

    };


    // GETTERS & SETTERS FOR AMBIENT, DIFFUSE, SPECULAR VALUES

    // Getters
    inline const Ambient& Light::GetAmbient() const
    {
        return mAmbientVal;
    }

    inline const Diffuse& Light::GetDiffuse() const
    {
        return mDiffuseVal;
    }

    inline const Specular& Light::GetSpecular() const
    {
        return mSpecularVal;
    }

    // Setters
    inline void Light::SetAmbient(const Ambient& ambient)
    {
        mAmbientVal = ambient;
    }

    inline void Light::SetDiffuse(const Diffuse& diffuse)
    {
        mDiffuseVal = diffuse;
    }

    inline void Light::SetSpecular(const Specular& specular)
    {
        mSpecularVal = specular;
    }

    // SETTERS FOR AMBIENT, DIFFUSE, SPECULAR LOCATION PATHS

    inline void Light::SetAmbientLocation(const AmbientLocation& ambientPath)
    {
        mAmbientPath = ambientPath;
    }

    inline void Light::SetDiffuseLocation(const DiffuseLocation& diffusePath)
    {
        mDiffusePath = diffusePath;
    }

    inline void Light::setSpecularLocation(const SpecularLocation& specularPath)
    {
        mSpecularPath = specularPath;
    }

}

#endif // _LIGHT_HPP_
