#version 450 core

out vec4 o_Colour;

struct Material {

    float shininess;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

in vec2 v_TexCoords0;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec3 v_camPos;

int PointlightNumber = 0;
uniform DirLight dirLight;
uniform PointLight pointLights[4];
uniform SpotLight spotLight;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;

Material material;

vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 camDir);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragpos, vec3 camDir);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragpos, vec3 camDir);

void  main()
{
	vec3 norm = normalize(v_Normal);
	vec3 camDir = normalize(v_camPos - v_FragPos);
	
	vec3 Result;	
	Result = CalculateDirLight(dirLight, norm, camDir);
	
	for(int i = 0; i < 4; i++)
	{
		Result += CalculatePointLight(pointLights[i], norm, v_FragPos, camDir);
	}
	
	//Result += CalculateSpotLight(spotLight, norm, v_FragPos, camDir);
	
	o_Colour = vec4(Result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 camDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(camDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(texture_height1, v_TexCoords0));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, v_TexCoords0));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, v_TexCoords0));
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 camDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(camDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(texture_height1, v_TexCoords0));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, v_TexCoords0));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, v_TexCoords0));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 camDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(camDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(texture_height1, v_TexCoords0));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, v_TexCoords0));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, v_TexCoords0));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}