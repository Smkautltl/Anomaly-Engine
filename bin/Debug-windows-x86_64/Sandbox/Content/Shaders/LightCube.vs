#version 450 core

layout(location = 0) in vec3 a_Position;

out vec4 v_Colour;

uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;
uniform mat4 u_ModelMatrix;

void  main()
{
	v_Colour = vec4(1.0);
	gl_Position = u_ProjMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0);	
}