struct Material
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};
uniform Material material;

uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform vec3 lightColor;

uniform sampler2D in_Texture;

varying vec2 ex_TexCoord;

in vec3 Normal;
in vec3 FragPos;

void main()
{
  vec3 ambient = lightColor * material.ambient;

  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = lightColor * (diff * material.diffuse);

  vec3 viewDir = normalize(cameraPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = lightColor * (spec * material.specular);

  vec4 tex = texture2D(in_Texture, ex_TexCoord); 

  vec3 phong = ambient * diffuse * specular;
  vec4 result = vec4(phong, 1.0) * tex;

  gl_FragColor = result;
}
