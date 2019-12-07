#version 450 core

layout(location = 0) out vec4 o_Colour;

in vec3 v_ObjectColour;
in vec3 v_LightColour;

void  main()
{
	o_Colour = vec4(v_LightColour * v_ObjectColour, 1.0);
}