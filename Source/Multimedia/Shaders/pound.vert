/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: pound.vert - GLSL pound shader
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
-- NOTES: Applies a circular distortion to vertices in the style of a "ground pound"
------------------------------------------------------------------------------------------------------------------*/

#version 120

uniform vec2 pound_position;
uniform float pound_total_radius;
uniform float pound_inner_radius;

void main()
{
    vec4 vertex = gl_ModelViewMatrix * gl_Vertex;
    vec2 offset = vertex.xy - pound_position;
    float len = length(offset);
    
	//Inside push
    if (len < pound_total_radius)
    {
        float push_distance = pound_inner_radius + len / pound_total_radius * (pound_total_radius - pound_inner_radius);
        vertex.xy = pound_position + normalize(offset) * push_distance;
    }
    
	//At push
    if(len == pound_total_radius)
	{
		float push_distance = pound_inner_radius + len / pound_inner_radius * pound_inner_radius;
	    vertex.xy = pound_position + normalize(offset) * push_distance;
    }
    
	//Tendrils
    if(vertex.x == pound_position.x)
    	vertex.y = vertex.y * vertex.y;
    if(vertex.y == pound_position.y)
    	vertex.x = vertex.x * vertex.x;
	
	//Apply transformation to the vertex
	gl_Position = gl_ProjectionMatrix * vertex;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_FrontColor = gl_Color;
}
