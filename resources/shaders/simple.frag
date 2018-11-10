struct Material
{
  sampler2D diffuse;
  vec3 specular;
  float shininess;
};
uniform Material material;

uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform vec3 lightColor;

varying vec2 ex_TexCoord;

in vec3 Normal;
in vec3 FragPos;


void main()
{
  vec3 lightAmbient = vec3(0.2, 0.2, 0.2);
  vec3 lightDiffuse = vec3(0.5, 0.5, 0.5);

  vec3 ambient = lightAmbient * vec3(texture(material.diffuse, ex_TexCoord));

  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = lightDiffuse * diff * vec3(texture(material.diffuse, ex_TexCoord));

  vec3 viewDir = normalize(cameraPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = lightColor * (spec * material.specular);

  gl_FragColor = vec4(ambient + diffuse + specular, 1.0);
}
