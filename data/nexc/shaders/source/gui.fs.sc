$input v_texcoord0, v_color0

#include "bgfx_shader.sh"

SAMPLER2D(s_texColor, 0);


void main() {
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);//v_color0;
}
