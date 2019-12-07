#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoords0;

out vec4 v_Colour;
out vec2 v_TexCoords0;

uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;
uniform mat4 u_ModelMatrix;

void  main()
{
	v_Colour = vec4(1.0);
	v_TexCoords0 = a_TexCoords0;
	gl_Position = u_ProjMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0);	
}