/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: lighting.frag - GLSL linear lighting shader
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
-- NOTES: Applies a simple single linear lighting model to the fragment
------------------------------------------------------------------------------------------------------------------*/

#version 120

uniform vec2 light_origin;
uniform vec3 light_colour;
uniform float light_falloff;
uniform float screen_height;

void main()
{		
	vec2 base_distance = gl_FragCoord.xy;
	base_distance.y = screen_height - base_distance.y;
	vec2 distance = light_origin - base_distance;
	
	//Calculate total distance and attenuation
	float linear_distance = length(distance);
	float attenuation = 1.0 / ( light_falloff * linear_distance + light_falloff * linear_distance);
	 
	vec4 lightColor = vec4(light_colour, 1.0);
	
	//Apply attenuation
	vec4 color = vec4(attenuation, attenuation, attenuation, 1.0) * lightColor;
	
	gl_FragColor=color;
}
