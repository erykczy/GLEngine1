#version 330 core

in vec2 TexCoord;

uniform vec4 ObjectColor;
uniform sampler2D MainTex;

out vec4 FragColor;

void main() {
	FragColor = texture(MainTex, TexCoord) * ObjectColor;
}