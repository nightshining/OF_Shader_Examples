/*{
	"DESCRIPTION": "VHS Glitch Style",
	"CREDIT": "Staffan Widegarn Åhlvik",
	"CATEGORIES": [
		"Stylize", "Glitch"
	],
	"INPUTS": [
		{
			"NAME": "inputImage",
			"TYPE": "image"
		},
		{
			"NAME": "autoScan",
			"TYPE": "bool",
			"DEFAULT": 1.0
		},
		{
			"NAME": "xScanline",
			"TYPE": "float",
			"DEFAULT": 0.5,
			"MIN": 0.0,
			"MAX": 1.0
		},
		{
			"NAME": "yScanline",
			"TYPE": "float",
			"DEFAULT": 0.0,
			"MIN": 0.0,
			"MAX": 1.0
		},
		{
			"NAME": "xScanlineSize",
			"TYPE": "float",
			"DEFAULT": 0.25,
			"MIN": 0.0,
			"MAX": 1.0
		},
		{
			"NAME": "yScanlineAmount",
			"TYPE": "float",
			"DEFAULT": 0.25,
			"MIN": -1.0,
			"MAX": 1.0
		},
		{
			"NAME": "grainLevel",
			"TYPE": "float",
			"DEFAULT": 0.0,
			"MIN": 0.0,
			"MAX": 3.0
		},
		{
			"NAME": "scanFollow",
			"TYPE": "bool",
			"DEFAULT": 1.0
		},
		{
			"NAME": "analogDistort",
			"TYPE": "float",
			"DEFAULT": 1.0,
			"MIN": 0.0,
			"MAX": 10.0
		},
		{
			"NAME": "bleedAmount",
			"TYPE": "float",
			"DEFAULT": 1.0,
			"MIN": 0.0,
			"MAX": 5.0
		},
		{
			"NAME": "bleedRange",
			"TYPE": "float",
			"DEFAULT": 1.0,
			"MIN": 0.0,
			"MAX": 2.0
		},
		{
			"NAME": "colorBleedL",
			"TYPE": "color",
			"DEFAULT": [
				0.8,
				0.0,
				0.2,
				1.0
			]
		},
		{
			"NAME": "colorBleedC",
			"TYPE": "color",
			"DEFAULT": [
				1.0,
				0.0,
				0.0,
				1.0
			]
		},
		{
			"NAME": "colorBleedR",
			"TYPE": "color",
			"DEFAULT": [
				0.8,
				0.2,
				0.0,
				1.0
			]
		}
	]
	
}*/




//	Based on https://github.com/staffantan/unity-vhsglitch
//	Converted by David Lublin / VIDVOX




float rand(vec3 co){
	return abs(mod(sin( dot(co.xyz ,vec3(12.9898,78.233,45.5432) )) * 43758.5453, 1.0));
}

void main()	{
	float	actualXLine = (!autoScan) ? xScanline : ((1.0+sin(0.34*TIME))/2.0 + (1.0+sin(TIME))/3.0 + (1.0+cos(2.1*TIME))/3.0 + (1.0+cos(0.027*TIME))/2.0)/3.0;
	vec2	loc = vv_FragNormCoord;
	vec4	vhs = IMG_NORM_PIXEL(inputImage, loc);
	float	dx = 1.0+xScanlineSize/25.0-abs(distance(loc.y, actualXLine));
	float	dy = (1.0-abs(distance(loc.y, yScanline)));
	
	dy = (dy > 0.5) ? 2.0 * dy : 2.0 * (1.0 - dy);
	
	//dy = ((int)(dy*15))/15.0;
	
	float	rX = (scanFollow) ? rand(vec3(dy,actualXLine,analogDistort)) : rand(vec3(dy,bleedAmount,analogDistort));
	float	xTime = (actualXLine > 0.5) ? 2.0 * actualXLine : 2.0 * (1.0 - xScanline);
	
	loc.x += yScanlineAmount * dy * 0.025 + analogDistort * rX/(RENDERSIZE.x/2.0);
	//float	white = (vhs.r+vhs.g+vhs.b)/3.0;
	
	if(dx > 1.0 - xScanlineSize / 25.0)
		loc.y = actualXLine;

	loc.x = mod(loc.x,1.0);
	loc.y = mod(loc.y,1.0);
	
	vec4	c = IMG_NORM_PIXEL(inputImage, loc);
	
	float	bleed = IMG_NORM_PIXEL(inputImage, loc + vec2(0.01, 0)).r;
	bleed += IMG_NORM_PIXEL(inputImage, loc + bleedRange * vec2(0.02, 0)).r;
	bleed += IMG_NORM_PIXEL(inputImage, loc + bleedRange * vec2(0.01, 0.01)).r;
	bleed += IMG_NORM_PIXEL(inputImage, loc - bleedRange * vec2(0.02, 0.02)).r;
	bleed += IMG_NORM_PIXEL(inputImage, loc - bleedRange * vec2(0., 0.02)).r;
	bleed /= 6.0;
	bleed *= bleedAmount;
	
	float x = (loc.x*320.0)/320.0;
	float y = (loc.y*240.0)/240.0;
	
	if (scanFollow)
		c -= rand(vec3(x, y, xTime)) * xTime / (5.0-grainLevel);
	else
		c -= rand(vec3(x, y, bleedAmount)) * (bleedAmount/20.0) / (5.0-grainLevel);
	
	vec4	colorBleed = (x < 0.5) ? mix(colorBleedL, colorBleedC, 2.0 * x) : mix(colorBleedR, colorBleedC, 2.0 - 2.0 * x);
	
	if (bleed > 0.1){
		if (scanFollow)
			c += bleed * max(xScanlineSize,xTime) * colorBleed;
		else
			c += bleed * colorBleed;
	}
	gl_FragColor = c;
}
