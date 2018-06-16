VSH��� u_transform   �  attribute vec4 a_color0;
attribute vec2 a_position;
attribute vec2 a_texcoord0;
varying vec4 v_color0;
varying vec2 v_texcoord0;
uniform mat3 u_transform;
void main ()
{
  vec3 tmpvar_1;
  tmpvar_1.z = 0.0;
  tmpvar_1.xy = a_position;
  vec4 tmpvar_2;
  tmpvar_2.w = 1.0;
  tmpvar_2.xyz = (u_transform * tmpvar_1);
  gl_Position = tmpvar_2;
  v_texcoord0 = a_texcoord0;
  v_color0 = a_color0;
}

 