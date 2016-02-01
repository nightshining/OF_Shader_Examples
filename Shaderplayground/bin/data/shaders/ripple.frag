
// ---> Shadertoy uniforms
uniform vec3 iResolution;
uniform float iGlobalTime;
uniform vec4 iMouse;
uniform sampler2D iChannel0; // Texture #1
uniform sampler2D iChannel1; // Texture #2
uniform sampler2D iChannel2; // Texture #3
uniform sampler2D iChannel3; // Texture #4
uniform vec4 iDate;


vec2 GetOffsetFromCenter(vec2 screenCoords, vec2 screenSize)
{
    vec2 halfScreenSize = screenSize / 2.0;
    
    return (screenCoords.xy - halfScreenSize) / min(halfScreenSize.x, halfScreenSize.y);
}


float EffectDuration = 1.0;
float EffectFadeInTimeFactor = 0.5;
float EffectWidth = 0.4;
float EffectMaxTexelOffset = 20.0;

vec2 GetDistortionTexelOffset(vec2 offsetDirection, float offsetDistance, float time)
{
    float progress = mod(time, EffectDuration) / EffectDuration;
    
    float halfWidth = EffectWidth / 2.0;
    float lower = 1.0 - smoothstep(progress - halfWidth, progress, offsetDistance);
    float upper = smoothstep(progress, progress + halfWidth, offsetDistance);
    
    float band = 1.0 - (upper + lower);
    
    
    float strength = 1.0 - progress;
    float fadeStrength = smoothstep(0.0, EffectFadeInTimeFactor, progress);
    
    float distortion = band * strength * fadeStrength;
    
    
    return distortion * offsetDirection * EffectMaxTexelOffset;
}


vec3 GetTextureOffset(vec2 coords, vec2 textureSize, vec2 texelOffset)
{
    vec2 texelSize = 1.0 / textureSize;
    vec2 offsetCoords = coords + texelSize * texelOffset;
    
    vec2 halfTexelSize = texelSize / 2.0;
    vec2 clampedOffsetCoords = clamp(offsetCoords, halfTexelSize, 1.0 - halfTexelSize);
    
    return texture2D(iChannel0, clampedOffsetCoords).rgb;
}


void main(void)
{
    float time = iGlobalTime;
    
    vec2 screenCoords = gl_FragCoord.xy;
    vec2 screenSize = iResolution.xy;
    
    
    vec2 offsetFromCenter = GetOffsetFromCenter(screenCoords, screenSize);
    vec2 offsetDirection = normalize(-offsetFromCenter);
    float offsetDistance = length(offsetFromCenter);
    
    
    vec2 offset = GetDistortionTexelOffset(offsetDirection, offsetDistance, time);
    
    
    vec2 coords = (gl_FragCoord.xy / screenSize);
    coords.y = 1.0 - coords.y;
    
    vec3 background = GetTextureOffset(coords, screenSize, offset);
    
     gl_FragColor = vec4(background, 1.0);
}
