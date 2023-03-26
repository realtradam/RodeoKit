$input v_color0, v_texcoord0, v_texcoord1

#include <bgfx_shader.sh>

SAMPLER2D(default_texture, 0);
SAMPLER2D(texture_0, 1);

//vec3 toLinear(vec3 _rgb)
//{
//	return pow(abs(_rgb), vec3_splat(2.2) );
//}
//
//vec4 toLinear(vec4 _rgba)
//{
//	return vec4(toLinear(_rgba.xyz), _rgba.w);
//}

void main()
{
  if(v_texcoord1 == 1.0)
  { 
    gl_FragColor = v_color0 * texture2D(texture_0, v_texcoord0.xy);
  } 
  else
  { 
    gl_FragColor = v_color0 * texture2D(default_texture, v_texcoord0.xy);
  } 
}
