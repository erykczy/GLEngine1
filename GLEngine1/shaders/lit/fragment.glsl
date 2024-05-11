#version 330 core

in vec2 TexCoord;

uniform vec4 ObjectColor;
uniform vec3 LightColor;
uniform sampler2D MainTex;

out vec4 FragColor;

void main() {
	FragColor = (texture(MainTex, TexCoord) * ObjectColor) * vec4(LightColor, 1.0);
}