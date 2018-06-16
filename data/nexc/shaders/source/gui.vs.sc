$input a_position, a_texcoord0, a_color0
$output v_texcoord0, v_color0

#include "bgfx_shader.sh"

uniform mat3 u_transform;

void main() {
	gl_Position = vec4(mul(u_transform, vec3(a_position, 1.0)), 1.0);
	v_texcoord0 = a_texcoord0;
	v_color0 = a_color0;
}