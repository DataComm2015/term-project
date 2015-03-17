/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: colourize.frag - GLSL colourization shader
--
-- PROGRAM: Project Spectre
--
-- DATE: February 9th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
--
-- NOTES: Adds or multiplies a given colour to the fragment
------------------------------------------------------------------------------------------------------------------*/

#version 120

uniform sampler2D texture;
uniform float multiply = 0;
uniform vec3 colour;

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	
	if(multiply > 0)
	{
		//Multiply by the colour
		pixel.xyz *= colour.xyz;
	}
	else
	{
		//Add the colour
		pixel.xyz += colour.xyz
	}
	
	gl_FragColor = pixel;
}
