#version 330 core
struct t_PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
struct t_Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform t_Material Material;
uniform int PointLightsCount;
#define MAX_POINT_LIGHTS_COUNT 64
uniform t_PointLight PointLights[MAX_POINT_LIGHTS_COUNT];
uniform vec3 ViewPos;
uniform sampler2D MainTex;

out vec4 FragColor;

vec3 calculatePointLight(t_PointLight light, vec3 viewDir) {
	vec3 lightDir = normalize(FragPos - light.position);
	float lightDistance = distance(FragPos, light.position);

	float attenuation = 1.0 / (light.constant + lightDistance * light.linear + lightDistance * lightDistance * light.quadratic);

	// diffuse
	float diff = dot(Normal, -lightDir);
	vec3 diffuse = vec3(texture(Material.diffuse, TexCoord)) * max(diff, 0.0) * light.diffuse * attenuation;
	
	// specular
	vec3 reflectDir = reflect(lightDir, Normal);
	float spec = pow(max(dot(-viewDir, reflectDir), 0.0), 32);
	vec3 specular = vec3(texture(Material.specular, TexCoord)) * spec * light.specular * attenuation;

	// ambient
	vec3 ambient = vec3(texture(Material.diffuse, TexCoord)) * light.ambient * attenuation;

	return ambient + diffuse + specular;
}

void main() {
	vec3 viewDir = normalize(FragPos - ViewPos);

	vec3 result = vec3(0.0);
	for(int i = 0; i < PointLightsCount; ++i) {
		result += calculatePointLight(PointLights[i], viewDir);
	}

	FragColor = vec4(result, 1.0);
}