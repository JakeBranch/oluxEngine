uniform mat4 in_Projection;
uniform mat4 in_Model;
uniform mat4 in_View;

attribute vec3 in_Position;
attribute vec2 in_TexCoord;
attribute vec3 in_Normal;

varying vec2 ex_TexCoord;

varying out vec3 Normal;
varying out vec3 FragPos;

void main()
{
  Normal = mat3(transpose(inverse(in_Model))) * in_Normal;
  FragPos = vec3(in_Model * vec4(in_Position, 1.0));

  gl_Position = in_Projection * in_View * in_Model * vec4(in_Position, 1.0);
  ex_TexCoord = in_TexCoord;	
}

