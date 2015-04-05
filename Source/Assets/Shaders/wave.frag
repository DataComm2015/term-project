/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: wave.frag - GLSL wave shader
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
-- NOTES: Applies a wave-like translation to vertices
------------------------------------------------------------------------------------------------------------------*/

#version 120

uniform float wave_phase;
uniform vec2 wave_amplitude;
uniform sampler2D texture;
varying vec2 texCoord;

void main()
{		
	vec2 aux = texCoord;
	
	aux.x = aux.x + (sin(aux.y*wave_phase)*wave_amplitude);
	aux.y = aux.y + (sin(texCoord.x*wave_phase)*wave_amplitude);
	
	gl_FragColor = texture2D(texture, aux);
}
