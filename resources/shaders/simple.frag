struct Material
{
  sampler2D diffuse;
  vec3 specular;
  float shininess;
};

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

#define MAX_NUM_POINT_LIGHTS 50
#define MAX_NUM_SPOT_LIGHTS 50

uniform int numOfPointLights;
uniform int numOfSpotLights;
uniform DirLight dirLight;
uniform PointLight pointLights[MAX_NUM_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_NUM_SPOT_LIGHTS];
uniform Material material;
uniform vec3 cameraPos;

varying vec2 ex_TexCoord;

in vec3 Normal;
in vec3 FragPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(cameraPos - FragPos);

    vec3 result = CalcDirLight(dirLight, norm, viewDir);

    for(int i = 0; i < numOfPointLights; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

    for(int i = 0; i < numOfSpotLights; i++)
        result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);

    gl_FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
  vec3 lightDir = normalize(-light.direction);

  float diff = max(dot(normal, lightDir), 0.0);

  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

  vec3 ambient = light.ambient * vec3(texture(material.diffuse, ex_TexCoord));
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, ex_TexCoord));
  vec3 specular = light.specular * (spec * material.specular);

  return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
   
    float diff = max(dot(normal, lightDir), 0.0);
 
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, ex_TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, ex_TexCoord));
    vec3 specular = light.specular * (spec * material.specular);

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}


vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{ 
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);
  
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, ex_TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, ex_TexCoord));
    vec3 specular = light.specular * (spec * material.specular);

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}
