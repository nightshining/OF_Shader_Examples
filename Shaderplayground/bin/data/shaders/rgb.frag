#define AMPLITUDE 0.2
#define SPEED 0.05

// ---> Shadertoy uniforms
uniform vec3 iResolution;
uniform float iGlobalTime;
uniform vec4 iMouse;
uniform sampler2D iChannel0; // Texture #1
uniform sampler2D iChannel1; // Texture #2
uniform sampler2D iChannel2; // Texture #3
uniform sampler2D iChannel3; // Texture #4
uniform vec4 iDate;


vec4 rgbShift( in vec2 p , in vec4 shift) {
    shift *= 2.0*shift.w - 1.0;
    vec2 rs = vec2(shift.x,-shift.y);
    vec2 gs = vec2(shift.y,-shift.z);
    vec2 bs = vec2(shift.z,-shift.x);
    
    float r = texture2D(iChannel0, p+rs, 0.0).x;
    float g = texture2D(iChannel0, p+gs, 0.0).y;
    float b = texture2D(iChannel0, p+bs, 0.0).z;
    
    return vec4(r,g,b,1.0);
}

vec4 noise( in vec2 p ) {
    return texture2D(iChannel1, p, 0.0);
}

vec4 vec4pow( in vec4 v, in float p ) {
    // Don't touch alpha (w), we use it to choose the direction of the shift
    // and we don't want it to go in one direction more often than the other
    return vec4(pow(v.x,p),pow(v.y,p),pow(v.z,p),v.w);
}

void main(void)
{
    vec2 p = gl_FragCoord.xy / iResolution.xy;
    vec4 c = vec4(0.0,0.0,0.0,1.0);
    
    // Elevating shift values to some high power (between 8 and 16 looks good)
    // helps make the stuttering look more sudden
    vec4 shift = vec4pow(noise(vec2(SPEED*iGlobalTime,2.0*SPEED*iGlobalTime/25.0 )),8.0)
    *vec4(AMPLITUDE,AMPLITUDE,AMPLITUDE,1.0);;
    
    c += rgbShift(p, shift);
    
    gl_FragColor = c;
}