#version 450 core

layout(location = 0) out vec4 o_Colour;

in vec3 v_Position;

void  main()
{
	o_Colour = vec4(0.5, 0.5, 1.0);
}