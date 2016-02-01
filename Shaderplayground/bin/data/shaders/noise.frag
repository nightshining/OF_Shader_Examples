// ---> Shadertoy uniforms
uniform vec3 iResolution;
uniform float iGlobalTime;
uniform vec4 iMouse;
uniform sampler2D iChannel0; // Texture #1
uniform sampler2D iChannel1; // Texture #2
uniform sampler2D iChannel2; // Texture #3
uniform sampler2D iChannel3; // Texture #4
uniform vec4 iDate;

vec2 distortUV(vec2 uv, vec2 nUV)
{
    float intensity = 0.01;
    float scale = 0.01;
    float speed = 0.25;
    
    
    nUV.x += (iGlobalTime)*speed;
    nUV.y += (iGlobalTime)*speed;
    vec2 noise= texture2D( iChannel0, nUV*scale).xy;
    
    uv += (-1.0+noise*2.0) * intensity;
    
    return uv;
}

void main( void )
{
    vec2 uv = gl_FragCoord.xy / iResolution.xy;
    vec2 nUV = uv;
    
    //uv=Tex Coords,  nUV=Noise Coords
    //Many Passes improves the effect
    //Or you could use a higher quality noise like perlin
    
    
    uv = distortUV(uv, nUV);
    uv = distortUV(uv, vec2(nUV.x+0.1,nUV.y+0.1));
    uv = distortUV(uv, vec2(nUV.x+0.2,nUV.y+0.2));
    uv = distortUV(uv, vec2(nUV.x+0.3,nUV.y+0.3));
    uv = distortUV(uv, vec2(nUV.x+0.4,nUV.y+0.4));
    uv = distortUV(uv, vec2(nUV.x+0.5,nUV.y+0.5));
    uv = distortUV(uv, vec2(nUV.x+0.6,nUV.y+0.6));
    uv = distortUV(uv, vec2(nUV.x+0.7,nUV.y+0.7));
    uv = distortUV(uv, vec2(nUV.x+0.8,nUV.y+0.8));
    uv = distortUV(uv, vec2(nUV.x+0.9,nUV.y+0.9));
    uv = distortUV(uv, vec2(nUV.x+0.15,nUV.y+0.15));
    uv = distortUV(uv, vec2(nUV.x+0.25,nUV.y+0.25));
    uv = distortUV(uv, vec2(nUV.x+0.35,nUV.y+0.35));
    uv = distortUV(uv, vec2(nUV.x+0.45,nUV.y+0.45));
    uv = distortUV(uv, vec2(nUV.x+0.55,nUV.y+0.55));
    uv = distortUV(uv, vec2(nUV.x+0.65,nUV.y+0.65));
    uv = distortUV(uv, vec2(nUV.x+0.75,nUV.y+0.75));
    uv = distortUV(uv, vec2(nUV.x+0.85,nUV.y+0.85));
    uv = distortUV(uv, vec2(nUV.x+0.95,nUV.y+0.95));
    
    
    
    
    vec4 color= texture2D( iChannel1, uv);
    
    
    gl_FragColor = vec4(color);
}