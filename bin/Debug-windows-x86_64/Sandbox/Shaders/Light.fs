#version 450 core

layout(location = 0) out vec4 o_Colour;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material m_material;
uniform Light l_Light;
uniform float time;

in vec2 v_TexCoords;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec3 v_ObjectColour;
uniform vec3 v_LightColour;
uniform vec3 v_LightPos;
uniform vec3 v_CamPos;

void  main()
{
	//Ambient
	vec3 Ambient = l_Light.ambient * vec3(texture(m_material.diffuse, v_TexCoords));

	//Diffuse
	vec3 Normal = normalize(v_Normal);
	vec3 LightDir = normalize(v_LightPos - v_FragPos);	
	float f_diffuse = max(dot(Normal, LightDir), 0.0);
	vec3 Diffuse = l_Light.diffuse * f_diffuse * vec3(texture(m_material.diffuse, v_TexCoords));
	
	//Specular
	vec3 camDir = normalize(v_CamPos - v_FragPos);
	vec3 reflectDir = reflect(-LightDir, Normal);
	float spec = pow(max(dot(camDir, reflectDir), 0.0), m_material.shininess);
	vec3 Specular = l_Light.specular * spec * vec3(texture(m_material.specular, v_TexCoords));

	//Emission
	vec3 Emission = vec3(0.0);
	if(texture(m_material.specular, v_TexCoords).r == 0.0)
	{
		Emission = texture(m_material.emission, v_TexCoords).rgb;
	
		Emission = texture(m_material.emission, v_TexCoords + vec2(0.0, time)).rgb;
		Emission = Emission * (sin(time) * 0.5 +0.5) * 2.0;
	}
	
	o_Colour = vec4(Ambient + Diffuse + Specular, 1.0);
}