#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords0;

out vec2 v_TexCoords0;
out vec3 v_FragPos;
out vec3 v_Normal;

uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;
uniform mat4 u_ModelMatrix;

void  main()
{
	v_FragPos = vec3(u_ModelMatrix * vec4(a_Position, 1.0));
	v_Normal = mat3(transpose(inverse(u_ModelMatrix))) * a_Normal;
	v_TexCoords0 = a_TexCoords0;
	gl_Position = u_ProjMatrix * u_ViewMatrix * vec4(v_FragPos, 1.0);	
}