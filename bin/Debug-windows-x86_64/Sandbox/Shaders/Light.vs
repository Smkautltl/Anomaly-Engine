#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

out vec2 v_TexCoords;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;
uniform mat4 u_ModelMatrix;

void  main()
{
	gl_Position = u_ProjMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0);	
	v_FragPos = vec3(u_ModelMatrix * vec4(a_Position, 1.0));
	v_Normal = mat3(transpose(inverse(u_ModelMatrix))) * a_Normal;
	v_TexCoords = a_TexCoords;
}