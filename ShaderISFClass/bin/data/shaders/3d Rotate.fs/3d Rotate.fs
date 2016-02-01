/*{
	"DESCRIPTION": "performs a 3d rotation",
	"CREDIT": "by VIDVOX",
	"CATEGORIES": [
		"Geometry Adjustment"
	],
	"INPUTS": [
		{
			"NAME": "inputImage",
			"TYPE": "image"
		},
		{
			"NAME": "xrot",
			"LABEL": "X rotate",
			"TYPE": "float",
			"MIN": 0.0,
			"MAX": 2.0,
			"DEFAULT": 2.0
		},
		{
			"NAME": "yrot",
			"LABEL": "Y rotate",
			"TYPE": "float",
			"MIN": 0.0,
			"MAX": 2.0,
			"DEFAULT": 0.5
		},
		{
			"NAME": "zrot",
			"LABEL": "Z rotate",
			"TYPE": "float",
			"MIN": 0.0,
			"MAX": 2.0,
			"DEFAULT": 5.0
		},
		{
			"NAME": "zoom",
			"LABEL": "Zoom Level",
			"TYPE": "float",
			"MIN": 0.0,
			"MAX": 1.0,
			"DEFAULT": 1.0
		}
	]
}*/


void main()
{
	gl_FragColor = IMG_THIS_PIXEL(inputImage);
}
