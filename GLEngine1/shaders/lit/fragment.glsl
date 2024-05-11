#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec4 ObjectColor;
uniform vec3 LightColor;
uniform vec3 LightPos;
uniform vec3 ViewPos;
uniform sampler2D MainTex;

out vec4 FragColor;

float ambientStrength = 0.1;
float specularStrength = 0.5;

vec4 getUnlitColor() {
	return texture(MainTex, TexCoord) * ObjectColor;
}

void main() {
	vec3 lightDir = normalize(FragPos - LightPos);
	vec3 viewDir = normalize(FragPos - ViewPos);

	// diffuse
	float diff = dot(Normal, -lightDir);
	vec3 diffuse = max(diff, 0.0) * LightColor;
	
	// specular
	vec3 reflectDir = reflect(lightDir, Normal);
	float spec = pow(max(dot(-viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * LightColor;

	// ambient
	vec3 ambient = ambientStrength * LightColor;

	FragColor = getUnlitColor() * vec4(ambient + diffuse + specular, 1.0);
}