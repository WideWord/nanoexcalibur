VSH      �   attribute vec2 a_position;
void main ()
{
  vec4 tmpvar_1;
  tmpvar_1.zw = vec2(0.5, 1.0);
  tmpvar_1.xy = a_position;
  gl_Position = tmpvar_1;
}

 