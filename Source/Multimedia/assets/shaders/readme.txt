Use of shaders (Lewis Scott, A00855385):

	blur.frag: Applies a box blur.
		Parameters:
			sampler2D texture: The texture applied to the fragment
			floar blur_radius: The radius of the blur
	
	colourize.frag: Applies a colour.
		Parameters:
			sampler2D texture: The texture applied to the fragment
			float multiply: 0 = Add colour, > 0 = Multiply colour
			vec3 colour: The colour to apply
	
	huesat.frag: Applies a hue, saturation and brightness modifier.
		Parameters:
			sampler2D texture: The texture applied to the fragment
			float contrast: The contrast to apply
			float brightness: The brightness to apply
			float hue: The hue modification to apply
			
	lighting.frag: Applies simple linear lighting with a single light source.
		Parameters:
			vec2 light_origin: The position of the light
			vec3 light_colour: The colour of the light
			float light_falloff: The falloff of the light
			float screen_height: The total height of the viewport, needed to invert the y-axis correctly
			
	pound.vert: Applies a 'ground-pound' effect over time.
		Parameters:
			vec2 pound_position: The origin of the pound
			float pound_total_radius: The outer radius of the pound
			float pound_inner_radius: The inner radius of the pound
			
	wave.vert: Applies a wave translation to vertices.
		Parameters:
			float wave_phase: The phase of the wave
			vec2 wave_amplitude: The amplitude(in pixels) of the wave
