#ifndef _LIGHTPARAMETERS_HPP_
#define _LIGHTPARAMETERS_HPP_

namespace Lighting
{
    using std::string;

    /************************** Ambient, Diffuse, Specular components **************************/

    // Ambient, Diffuse, Specular values
    struct Ambient
    {
        explicit Ambient(const glm::vec3& a_ambient)
        : ambient {a_ambient}
        {}

        glm::vec3   ambient;
    };

    struct Diffuse
    {
        explicit Diffuse(const glm::vec3& a_diffuse)
        : diffuse {a_diffuse}
        {}

        glm::vec3   diffuse;
    };

    struct Specular
    {
        explicit Specular(const glm::vec3& a_specular)
        : specular {a_specular}
        {}

        glm::vec3   specular;
    };

    // Ambient, Diffuse, Specular locations
    struct AmbientLocation
    {
        explicit AmbientLocation(const string& a_ambientLocation)
        : ambientLocation { a_ambientLocation }
        {}

        string     ambientLocation;
    };

    struct DiffuseLocation
    {
        explicit DiffuseLocation(const string& a_diffuseLocation)
        : diffuseLocation { a_diffuseLocation }
        {}

        string     diffuseLocation;
    };

    struct SpecularLocation
    {
        explicit SpecularLocation(const string& a_specularLocation)
        : specularLocation { a_specularLocation }
        {}

        string     specularLocation;
    };


    /************************** Direction, Position components **************************/

    // Direction component and  his location
    struct Direction
    {
        explicit Direction(const glm::vec3& a_direction)
        : direction {a_direction}
        {}

        glm::vec3   direction;
    };

    struct DirectionLocation
    {
        explicit DirectionLocation(const string& a_directionLocation)
        : directionLocation { a_directionLocation }
        {}

        string     directionLocation;
    };

    // Position component and location
    struct Position
    {
        explicit Position(const glm::vec3& a_position)
        : position {a_position}
        {}

        glm::vec3   position;
    };

    struct PositionLocation
    {
        explicit PositionLocation(const string& a_positionLocation)
        : positionLocation { a_positionLocation }
        {}

        string     positionLocation;
    };


    /************************** Attenuation components **************************/

    // Constant component and location
    struct Constant
    {
        explicit Constant(float a_constant)
        : constant {a_constant}
        {}

        float   constant;
    };

    struct ConstantLocation
    {
        explicit ConstantLocation(const string& a_constantLocation)
        : constantLocation { a_constantLocation }
        {}

        string     constantLocation;
    };

    // Linear component and location
    struct Linear
    {
        explicit Linear(float a_linear)
        : linear {a_linear}
        {}

        float   linear;
    };

    struct LinearLocation
    {
        explicit LinearLocation(const string& a_linearLocation)
        : linearLocation { a_linearLocation }
        {}

        string     linearLocation;
    };

    // Quadratic component and location
    struct Quadratic
    {
        explicit Quadratic(float a_quadratic)
        : quadratic {a_quadratic}
        {}

        float   quadratic;
    };

    struct QuadraticLocation
    {
        explicit QuadraticLocation(const string& a_quadraticLocation)
        : quadraticLocation { a_quadraticLocation }
        {}

        string     quadraticLocation;
    };


    /************************** SpotLight components **************************/

    // CutOff component and location
    struct CutOff
    {
        explicit CutOff(float a_cutOff)
        : cutOff {a_cutOff}
        {}

        float   cutOff;
    };

    struct CutOffLocation
    {
        explicit CutOffLocation(const string& a_cutOffLocation)
        : cutOffLocation { a_cutOffLocation }
        {}

        string     cutOffLocation;
    };

    // OuterCutOff component and location
    struct OuterCutOff
    {
        explicit OuterCutOff(float a_outerCutOff)
        : outerCutOff {a_outerCutOff}
        {}

        float   outerCutOff;
    };

    struct OuterCutOffLocation
    {
        explicit OuterCutOffLocation(const string& a_outerCutOffLocation)
        : outerCutOffLocation { a_outerCutOffLocation }
        {}

        string     outerCutOffLocation;
    };
}


#endif // _LIGHTPARAMETERS_HPP_
