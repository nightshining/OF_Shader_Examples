#define OCTAVES  8.0

#define LIVE_SMOKE 0

// ---> Shadertoy uniforms
uniform vec3 iResolution;
uniform float iGlobalTime;
uniform vec4 iMouse;
uniform sampler2D iChannel0; // Texture #1
uniform sampler2D iChannel1; // Texture #2
uniform sampler2D iChannel2; // Texture #3
uniform sampler2D iChannel3; // Texture #4
uniform vec4 iDate;


const int noiseSwirlSteps = 2;
const float noiseSwirlValue = 1.;
const float noiseSwirlStepValue = noiseSwirlValue / float(noiseSwirlSteps);

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float rand2(vec2 co){
    return fract(cos(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

// Rough Value noise implementation
float valueNoiseSimple(vec2 vl) {
    float minStep = 1.0 ;
    
    vec2 grid = floor(vl);
    vec2 gridPnt1 = grid;
    vec2 gridPnt2 = vec2(grid.x, grid.y + minStep);
    vec2 gridPnt3 = vec2(grid.x + minStep, grid.y);
    vec2 gridPnt4 = vec2(gridPnt3.x, gridPnt2.y);
    
    float s = rand2(grid);
    float t = rand2(gridPnt3);
    float u = rand2(gridPnt2);
    float v = rand2(gridPnt4);
    
    float x1 = smoothstep(0., 1., fract(vl.x));
    float interpX1 = mix(s, t, x1);
    float interpX2 = mix(u, v, x1);
    
    float y = smoothstep(0., 1., fract(vl.y));
    float interpY = mix(interpX1, interpX2, y);
    
    return interpY;
}

float fractalNoise(vec2 vl) {
    float persistance = 2.0;
    float amplitude = 0.5;
    float rez = 0.0;
    vec2 p = vl;
    
    for (float i = 0.0; i < OCTAVES; i++) {
        rez += amplitude * valueNoiseSimple(p);
        amplitude /= persistance;
        p *= persistance;
    }
    return rez;
}

float complexFBM(vec2 p) {
    float slow = iGlobalTime / 10.;
    float fast = iGlobalTime / 2.;
    vec2 offset1 = vec2(slow, 0.); // Main front
    
#if LIVE_SMOKE
    vec2 offset2 = vec2(valueNoiseSimple(p + fast) * 2., 0.); // sub fronts
#else
    vec2 offset2 = vec2(sin(fast) * 0.1, 0.); // sub fronts
#endif
    
    return fractalNoise( p + offset1 + fractalNoise(
                                                    p + fractalNoise(
                                                                     p + 2. * fractalNoise(p - offset2)
                                                                     )
                                                    )
                        );
}


void main( void )
{
    vec2 uv = gl_FragCoord.xy / iResolution.xy;
    
    vec3 blueColor = vec3(0.529411765, 0.807843137, 0.980392157);
    vec3 orangeColor2 = vec3(0.01, 0.01, 0.01);
    
    vec3 rez = mix(orangeColor2, blueColor, complexFBM(uv));
    
    gl_FragColor = vec4(rez, 1.0);
    
}