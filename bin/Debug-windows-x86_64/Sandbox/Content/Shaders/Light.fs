#version 450 core

layout(location = 0) out vec4 o_Colour;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};
uniform Material m_material;

struct DirLight
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirLight dirlight;

struct PointLight
{
	vec3 position;
	
	float constant;
	float linear;
	float quadratic;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
#define NR_POINT_LIGHTS 4
uniform PointLight pointlights[NR_POINT_LIGHTS];

uniform float time;

in vec2 v_TexCoords;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec3 v_ObjectColour;
uniform vec3 v_LightColour;
uniform vec3 v_CamPos;

vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 camDir)
{
	vec3 lightDir = normalize(-light.direction);
	
	//Diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	
	//Specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(camDir, reflectDir), 0.0), m_material.shininess);
	
	//Calculation
	vec3 ambient = light.ambient * vec3(texture(m_material.diffuse, v_TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(m_material.diffuse, v_TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(m_material.specular, v_TexCoords));
	
	return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 camDir, vec3 fragPos)
{
	vec3 lightDir = normalize(-light.position - fragPos);
	
	//Diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	
	//Specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(camDir, reflectDir), 0.0), m_material.shininess);
	
	//Attenuation
	float f_distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * f_distance + light.quadratic * (f_distance * f_distance)); 
	
	vec3 ambient = light.ambient * vec3(texture(m_material.diffuse, v_TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(m_material.diffuse, v_TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(m_material.specular, v_TexCoords));
	
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	
	return (ambient + diffuse + specular);
}

void  main()
{
	vec3 norm = normalize(v_Normal);
	vec3 camDir = normalize(v_CamPos - v_FragPos);
	
	vec3 result = CalculateDirLight(dirlight, norm,camDir);
	
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result += CalculatePointLight(pointlights[i], norm, camDir, v_FragPos);
	}
	
	o_Colour = vec4(result, 1.0);
}

