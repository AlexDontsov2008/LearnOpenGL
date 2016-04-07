#version 430 core

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


vec3 CalcDirLight(DirLight light, vec3 normal, Material mat, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, Material mat, vec3 fragPos, vec3 viewDir);

const unsigned int NR_POINT_LIGHTS = 2;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;


uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];

out vec4 color;


void main()
{
    // Properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0f, 0.0f, 0.0f);

    // Direction light
    result += CalcDirLight(dirLight, norm, material, viewDir);

    // Point lights
    for (int i = 0; i < NR_POINT_LIGHTS; ++i)
    {
        result += CalcPointLight(pointLights[i], norm, material, FragPos, viewDir);
    }


    color = vec4(result, 1.0f);
}

vec3 CalcDirLight(DirLight light, vec3 normal, Material mat, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0f);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), mat.shininess);

    // Combine results
    vec3 ambient  = light.ambient  * vec3(texture(mat.texture_diffuse1, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(mat.texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(mat.texture_specular1, TexCoords));

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, Material mat, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0f);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), mat.shininess);

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Combine results
    vec3 ambient = light.ambient * vec3(texture(mat.texture_diffuse1, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(mat.texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(mat.texture_specular1, TexCoords));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}
