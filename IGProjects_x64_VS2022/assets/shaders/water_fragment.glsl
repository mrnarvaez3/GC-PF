#version 430 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;

struct DirLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	bool enabled;
};

struct PosLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
	float linear;
	float quadratic;
	bool enabled;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
	bool enabled;
};

const int NR_DIR_LIGHTS = 2;
const int NR_POS_LIGHTS = 4;
const int NR_SPOT_LIGHTS = 4;

uniform DirLight dirLights[NR_DIR_LIGHTS];
uniform PosLight posLights[NR_POS_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

uniform bool wireframeEnabled;
uniform float wireframeWidth;
uniform vec3 wireframeColor;

in vec3 FragPos;
in vec3 FlatNormal;
noperspective in vec3 Bary;

out vec4 FragColor;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), max(material.shininess, 1.0));

	vec3 ambient  = light.ambient * material.ambient;
	vec3 diffuse  = light.diffuse * diff * material.diffuse;
	vec3 specular = light.specular * spec * material.specular;
	return ambient + diffuse + specular;
}

vec3 calcPosLight(PosLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), max(material.shininess, 1.0));

	float dist = distance(light.position, fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	vec3 ambient  = light.ambient * material.ambient;
	vec3 diffuse  = light.diffuse * diff * material.diffuse;
	vec3 specular = light.specular * spec * material.specular;
	return attenuation * (ambient + diffuse + specular);
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), max(material.shininess, 1.0));

	float dist = distance(light.position, fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	vec3 ambient  = light.ambient * material.ambient;
	vec3 diffuse  = light.diffuse * diff * material.diffuse;
	vec3 specular = light.specular * spec * material.specular;
	return attenuation * (ambient + intensity * (diffuse + specular));
}

void main()
{
	vec3 norm = normalize(FlatNormal);
	vec3 viewDir = normalize(-FragPos);
	vec3 result = vec3(0);

	for (int i = 0; i < NR_DIR_LIGHTS; i++)
		if (dirLights[i].enabled)
			result += calcDirLight(dirLights[i], norm, viewDir);

	for (int i = 0; i < NR_POS_LIGHTS; i++)
		if (posLights[i].enabled)
			result += calcPosLight(posLights[i], norm, FragPos, viewDir);

	for (int i = 0; i < NR_SPOT_LIGHTS; i++)
		if (spotLights[i].enabled)
			result += calcSpotLight(spotLights[i], norm, FragPos, viewDir);

	// Wireframe overlay con coordenadas baricentricas
	if (wireframeEnabled) {
		float minBary = min(min(Bary.x, Bary.y), Bary.z);
		float edge = smoothstep(0.0, wireframeWidth * 0.02, minBary);
		result = mix(wireframeColor, result, edge);
	}

	FragColor = vec4(result, 1.0);
}
