/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: huesat.frag - GLSL hue and saturation shader
--
-- PROGRAM: Project Spectre
--
-- FUNCTIONS:
-- float saturate(float);
-- vec3 rgb_to_hsv(vec3);
-- vec3 hsv_to_rgb(vec3);
--
-- DATE: February 9th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott, sam@lolengine.net
--
-- NOTES: Modifies the hue, brightness and contrast of the fragment.
--		  HSV conversion code taken from: http://lolengine.net/blog/2013/07/27/rgb-to-hsv-in-glsl
------------------------------------------------------------------------------------------------------------------*/

#version 120

uniform sampler2D texture;
uniform float contrast = 0;
uniform float brightness = 0;
uniform float hue = 0;

float saturate(float);
vec3 rgb_to_hsv(vec3);
vec3 hsv_to_rgb(vec3);

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec3 fragHSV = rgb_to_hsv(pixel.rgb).xyz;
	fragHSV.x += hue; //Apply the hue modifier
	pixel = vec4(hsv_to_rgb(fragHSV), pixel.w);
	
	//Apply brightness modifier
	pixel.x += brightness;
	pixel.y += brightness;
	pixel.z += brightness;
	
	//Apply contrast modifier
	pixel.x = saturate(pixel.x);
	pixel.y = saturate(pixel.y);
	pixel.z = saturate(pixel.z);
	
	gl_FragColor = pixel;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: saturate
--
-- DATE: February 9th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
--
-- INTERFACE: float saturate(float n);
--					float n: The contrast multiplier
--
-- RETURNS: float: the saturated element
--
-- NOTES:
-- Applies a given contrast to a pixel or fragment element
----------------------------------------------------------------------------------------------------------------------*/
float saturate(float n)
{
	if(n > 0.5f)
		return n + contrast;
	else
		return n - contrast;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: rgb_to_hsv
--
-- DATE: July 27th, 2013
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: sam@lolengine.net
--
-- PROGRAMMER: sam@lolengine.net
--
-- INTERFACE: vec3 rgb_to_hsv(vec3 c)
--					vec3 c: The original RGB value
--
-- RETURNS: vec3: The converted HSV value
--
-- NOTES:
-- Converts an RGB(red-green-blue) value to an HSV(hue-saturation-lighting value) value
----------------------------------------------------------------------------------------------------------------------*/
vec3 rgb_to_hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: hsv_to_rgb
--
-- DATE: July 27th, 2013
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: sam@lolengine.net
--
-- PROGRAMMER: sam@lolengine.net
--
-- INTERFACE: vec3 hsv_to_rgb(vec3 c)
--					vec3 c: The original HSV value
--
-- RETURNS: vec3: The converted RGB value
--
-- NOTES:
-- Converts an HSV(hue-saturation-lighting value) value to an RGB(red-green-blue) value
----------------------------------------------------------------------------------------------------------------------*/
vec3 hsv_to_rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}
