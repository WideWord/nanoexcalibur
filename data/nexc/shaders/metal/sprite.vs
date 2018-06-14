VSH      �  using namespace metal;
struct xlatMtlShaderInput {
  float2 a_position [[attribute(0)]];
};
struct xlatMtlShaderOutput {
  float4 gl_Position [[position]];
};
struct xlatMtlShaderUniform {
};
vertex xlatMtlShaderOutput xlatMtlMain (xlatMtlShaderInput _mtl_i [[stage_in]], constant xlatMtlShaderUniform& _mtl_u [[buffer(0)]])
{
  xlatMtlShaderOutput _mtl_o;
  float4 tmpvar_1 = 0;
  tmpvar_1.zw = float2(0.5, 1.0);
  tmpvar_1.xy = _mtl_i.a_position;
  _mtl_o.gl_Position = tmpvar_1;
  return _mtl_o;
}

 