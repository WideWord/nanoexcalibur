FSH���  ?  using namespace metal;
struct xlatMtlShaderInput {
  float4 v_color0;
  float2 v_texcoord0;
};
struct xlatMtlShaderOutput {
  float4 gl_FragColor;
};
struct xlatMtlShaderUniform {
};
fragment xlatMtlShaderOutput xlatMtlMain (xlatMtlShaderInput _mtl_i [[stage_in]], constant xlatMtlShaderUniform& _mtl_u [[buffer(0)]]
  ,   texture2d<float> s_texColor [[texture(0)]], sampler _mtlsmp_s_texColor [[sampler(0)]])
{
  xlatMtlShaderOutput _mtl_o;
  _mtl_o.gl_FragColor = (_mtl_i.v_color0 * s_texColor.sample(_mtlsmp_s_texColor, (float2)(_mtl_i.v_texcoord0)));
  return _mtl_o;
}

 