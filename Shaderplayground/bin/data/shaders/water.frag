
float SCALE = 1.;

#define ANIM true

// ---> Shadertoy uniforms
uniform vec3 iResolution;
uniform float iGlobalTime;
uniform vec4 iMouse;
uniform sampler2D iChannel0; // Texture #1
uniform sampler2D iChannel1; // Texture #2
uniform sampler2D iChannel2; // Texture #3
uniform sampler2D iChannel3; // Texture #4
uniform vec4 iDate;

// --- noise functions from https://www.shadertoy.com/view/XslGRr
// Created by inigo quilez - iq/2013
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.

mat3 m = mat3( 0.00,  0.80,  0.60,
              -0.80,  0.36, -0.48,
              -0.60, -0.48,  0.64 );

float hash( float n )
{
    return fract(sin(n)*43758.5453);
}

float noise( in vec3 x )
{
    vec3 p = floor(x);
    vec3 f = fract(x);
    
    f = f*f*(3.0-2.0*f);
    
    float n = p.x + p.y*57.0 + 113.0*p.z;
    
    float res = mix(mix(mix( hash(n+  0.0), hash(n+  1.0),f.x),
                        mix( hash(n+ 57.0), hash(n+ 58.0),f.x),f.y),
                    mix(mix( hash(n+113.0), hash(n+114.0),f.x),
                        mix( hash(n+170.0), hash(n+171.0),f.x),f.y),f.z);
    return res;
}

float fbm( vec3 p )
{
    float f;
    f  = 0.5000*noise( p ); p = m*p*2.02;
    f += 0.2500*noise( p ); p = m*p*2.03;
    f += 0.1250*noise( p ); p = m*p*2.01;
    f += 0.0625*noise( p );
    return f;
}
// --- End of: Created by inigo quilez --------------------
float mynoise ( vec3 p)
{
    return noise(p);
    //return .5+.5*sin(50.*noise(p));
}
float myfbm( vec3 p )
{
    float f;
    f  = 0.5000*mynoise( p ); p = m*p*2.02;
    f += 0.2500*mynoise( p ); p = m*p*2.03;
    f += 0.1250*mynoise( p ); p = m*p*2.01;
    f += 0.0625*mynoise( p ); p = m*p*2.05;
    f += 0.0625/2.*mynoise( p ); p = m*p*2.02;
    f += 0.0625/4.*mynoise( p );
    return f;
}
float myfbm2( vec3 p )
{
    float f;
    f  = 1. - 0.5000*mynoise( p ); p = m*p*2.02;
    f *= 1. - 0.2500*mynoise( p ); p = m*p*2.03;
    f *= 1. - 0.1250*mynoise( p ); p = m*p*2.01;
    f *= 1. - 0.0625*mynoise( p ); p = m*p*2.05;
    f *= 1. - 0.0625/2.*mynoise( p ); p = m*p*2.02;
    f *= 1. - 0.0625/4.*mynoise( p );
    return f;
}

void main( void )
{
    vec2 uv = gl_FragCoord.xy / iResolution.y;
    vec3 v;
    vec3 p = 4. * vec3(uv,0.) + iGlobalTime * (.1,.7,1.2);
    float x = myfbm(p);
    //v = vec3(x);
    v = (.5+.5*sin(x*vec3(30.,20.,10.)*SCALE))/SCALE;
    float g = 1.;
    //g = pow(length(v),1.);
    //g =  .5*noise(8.*m*m*m*p)+.5; g = 2.*pow(g,3.);
    v *= g;
    vec3 Ti = texture2D(iChannel0,.02*v.xy+gl_FragCoord.xy / iResolution.xy).rgb*1.4-.2;
    vec3 Tf = texture2D(iChannel1,.02*v.xy+gl_FragCoord.xy / iResolution.xy).rgb;
    vec3 T=Ti;
    // T = Ti+(1.-Ti)*Tf;
    vec3 T1,T2;
    T1 = vec3(0.,0.,1.); T1 *= .5*(T+1.);
    T2 = vec3(1.,1.,1.); //T2 = 1.2*Ti*vec3(1.,.8,.6)-.2;
    v = mix(mix(T1,1.*Tf,.5),T2,T);
    gl_FragColor = vec4(v,1.0);
    
}