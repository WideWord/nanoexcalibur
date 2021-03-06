VSHo>< u_transform   �  using namespace metal;
struct xlatMtlShaderInput {
  float2 a_position [[attribute(0)]];
  float2 a_texcoord0 [[attribute(1)]];
};
struct xlatMtlShaderOutput {
  float4 gl_Position [[position]];
  float2 v_texcoord0;
};
struct xlatMtlShaderUniform {
  float3x3 u_transform;
};
vertex xlatMtlShaderOutput xlatMtlMain (xlatMtlShaderInput _mtl_i [[stage_in]], constant xlatMtlShaderUniform& _mtl_u [[buffer(0)]])
{
  xlatMtlShaderOutput _mtl_o;
  float3 tmpvar_1 = 0;
  tmpvar_1.z = 0.0;
  tmpvar_1.xy = _mtl_i.a_position;
  float4 tmpvar_2 = 0;
  tmpvar_2.w = 1.0;
  tmpvar_2.xyz = (_mtl_u.u_transform * tmpvar_1);
  _mtl_o.gl_Position = tmpvar_2;
  _mtl_o.v_texcoord0 = _mtl_i.a_texcoord0;
  return _mtl_o;
}

 