#version 450 core

layout(location = 0) out vec4 o_Colour;

in vec3 v_Position;
in vec4 v_Colour;

void  main()
{
	o_Colour = vec4(v_Position * 0.5 + 0.5, 1.0);
	o_Colour = v_Colour;
}