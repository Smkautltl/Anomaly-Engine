#version 450 core

layout(location = 0) out vec4 o_Colour;

in vec4 v_Colour;
in vec2 v_TexCoords0;

uniform sampler2D u_Texture0;

void  main()
{
	o_Colour = texture(u_Texture0, v_TexCoords0) * vec4(v_Colour);
}