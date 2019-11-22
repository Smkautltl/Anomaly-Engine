#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Colour;

uniform mat4 u_ViewProjMatrix;
uniform mat4 u_Transform;

out vec3 v_Position;
out vec4 v_Colour;

void  main()
{
	v_Position = a_Position;
	v_Colour = a_Colour;
	gl_Position = u_ViewProjMatrix * u_Transform * vec4(a_Position, 1.0);	
}