#version 450 core

out vec4 o_Colour;

in vec2 v_TexCoords0;

uniform sampler2D texture_diffuse1;

void  main()
{
	o_Colour = texture(texture_diffuse1, v_TexCoords0);
}