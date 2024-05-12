#version 330 core
struct t_Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
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
uniform t_Light Light;
uniform vec3 ViewPos;
uniform sampler2D MainTex;

out vec4 FragColor;

void main() {
	vec3 lightDir = normalize(FragPos - Light.position);
	vec3 viewDir = normalize(FragPos - ViewPos);

	// diffuse
	float diff = dot(Normal, -lightDir);
	vec3 diffuse = vec3(texture(Material.diffuse, TexCoord)) * max(diff, 0.0) * Light.diffuse;
	
	// specular
	vec3 reflectDir = reflect(lightDir, Normal);
	float spec = pow(max(dot(-viewDir, reflectDir), 0.0), 32);
	vec3 specular = vec3(texture(Material.specular, TexCoord)) * spec * Light.specular;

	// ambient
	vec3 ambient = vec3(texture(Material.diffuse, TexCoord)) * Light.ambient;

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}