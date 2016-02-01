
uniform vec3 iResolution;
uniform float iGlobalTime;
uniform vec4 iMouse;
uniform sampler2D iChannel0; // Texture #1
uniform sampler2D iChannel1; // Texture #2
uniform sampler2D iChannel2; // Texture #3
uniform sampler2D iChannel3; // Texture #4
uniform vec4 iDate;

const float PI = 3.14159265;

float time = iGlobalTime * 0.02;

void main( void ) {
    
    float color1, color2, color;
    
    color1 = (sin(dot(gl_FragCoord.xy,vec2(sin(time * 6.0),cos(time*3.0)))*0.02 + time * iMouse.x) + 1.0)/2.0;
    
    vec2 center = vec2(640.0/2.0, 360.0/2.0) + vec2(640.0/2.0*sin(-time*3.0),360.0/2.0*cos(-time*0.05));
    
    color2 = (cos(length(gl_FragCoord.xy - center) * 0.05) + 1.0) / 4.0;
    
    color = (color1 + color2) / 1.0;
    
    float red	= (cos(PI * color / 0.5 + time * 3.0) + 1.0) / 2.0;
    float green	= (sin(PI * color / 0.5 + cos(time) * 3.0) + 1.0) / 2.0;
    float blue	= (sin(time * 6.0) + 1.0) / sin(time) * 5.0;
    
    gl_FragColor = vec4(red, green, blue, 1.0);
}