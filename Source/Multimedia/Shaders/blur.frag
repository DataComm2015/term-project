/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: blur.frag - GLSL box blur shader
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
-- NOTES: Performs a blur using a 3x3 box kernel
------------------------------------------------------------------------------------------------------------------*/

#version 120

uniform sampler2D texture;
uniform float blur_radius;

void main()
{
	vec2 offx = vec2(blur_radius, 0.0);
	vec2 offy = vec2(0.0, blur_radius);

	/* 
		blur kernel:
		+ 1 2 1 +
		| 2 4 2 |
		+ 1 2 1 +
	*/
	
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy)               * 4.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offx)        * 2.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offx)        * 2.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offy)        * 2.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offy)        * 2.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offx - offy) * 1.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offx + offy) * 1.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offx - offy) * 1.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offx + offy) * 1.0;

	//16.0 is the sum of the kernel
	gl_FragColor =  gl_Color * (pixel / 16.0);
}
