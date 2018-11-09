struct Material
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

uniform Material material;

uniform sampler2D in_Texture;

varying vec2 ex_TexCoord;

void main()
{
  vec3 ambient = vec3(1.0f, 1.0f, 1.0f) * material.ambient;
  vec3 diffuse = vec3(1.0f, 1.0f, 1.0f) * material.diffuse;
  vec3 specular = vec3(1.0f, 1.0f, 1.0f) * material.specular * material.shininess;
  vec3 result = ambient * diffuse * specular;

  vec4 tex = texture2D(in_Texture, ex_TexCoord); 
  gl_FragColor = tex * vec4(result, 1.0f);
}
