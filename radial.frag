uniform sampler2D tex0;
uniform vec2 resolution; // screen resolution
#define T texture2D(tex0,.5+(p.xy*=.992))
void main() 
{
  vec2 p = gl_FragCoord.xy/resolution-.5;
  vec2 o = T.rb;
  for (float i=0.;i<100.;i++) 
    p.y += pow(max(0.,.5-length(T.rg)),2.)*exp(-i*.08);
  gl_FragColor=vec4(o*o+p.z,1);
}