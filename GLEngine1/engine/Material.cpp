#pragma once
#include "engine/Material.h"

#include "engine/Texture2D.h"
#include "engine/components/PointLight.h"
#include "engine/components/Camera.h"
#include "engine/components/Transform.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <fstream>
#include <sstream>

Material::Material(const char* vertexPath, const char* fragmentPath) : m_vertexPath(vertexPath), m_fragmentPath(fragmentPath) {
	m_programId = link();
}

Material::~Material() {
	glDeleteProgram(m_programId);
}

Material& Material::operator=(const Material& source) {
	if (&source == this) return *this;
	glDeleteProgram(m_programId);
	m_vertexPath = source.m_vertexPath;
	m_fragmentPath = source.m_fragmentPath;
	return *this;
}

Material::Material(Material&& source) noexcept {
	m_programId = source.m_programId;
	m_vertexPath = source.m_vertexPath;
	m_fragmentPath = source.m_fragmentPath;

	source.m_programId = 0;
}

Material& Material::operator=(Material&& source) noexcept {
	if (&source == this) return *this;
	glDeleteProgram(m_programId);

	m_programId = source.m_programId;
	m_vertexPath = source.m_vertexPath;
	m_fragmentPath = source.m_fragmentPath;

	source.m_programId = 0;
	return *this;
}

void Material::applySceneData(Scene* scene) {
	setVector3("ViewPos", scene->getActiveCamera()->transform->position);
	applyLighting(scene);
}

void Material::applyLighting(Scene* scene)
{
	auto lights{ scene->getGameObjects<PointLight>() };
	setInt("PointLightsCount", static_cast<int>(lights.size()));
	for(int i = 0; i < lights.size(); ++i) {
		std::string index{ static_cast<std::string>("PointLights[") + std::to_string(i) + "]." };
		setVector3(index + "position", lights[i]->transform->position);
		setVector3(index + "ambient", lights[i]->ambient);
		setVector3(index + "diffuse", lights[i]->diffuse);
		setVector3(index + "specular", lights[i]->specular);

		setFloat(index + "constant", lights[i]->constant);
		setFloat(index + "linear", lights[i]->linear);
		setFloat(index + "quadratic", lights[i]->quadratic);
	}
}

void Material::setSpaceTransformMatricies(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	setMatrix4x4("model", modelMatrix);
	setMatrix4x4("view", viewMatrix);
	setMatrix4x4("projection", projectionMatrix);
}

void Material::setTextureUnit(std::string_view uniformName, int textureUnit) {
	glProgramUniform1i(m_programId, findUniformLocation(uniformName), textureUnit);
}

void Material::setMatrix4x4(std::string_view uniformName, const glm::mat4& matrix) {
	glProgramUniformMatrix4fv(m_programId, findUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Material::setVector3(std::string_view uniformName, const glm::vec3& vec) {
	glProgramUniform3fv(m_programId, findUniformLocation(uniformName), 1, glm::value_ptr(vec));
}

void Material::setVector4(std::string_view uniformName, const glm::vec4& vec)
{
	glProgramUniform4fv(m_programId, findUniformLocation(uniformName), 1, glm::value_ptr(vec));
}

void Material::setFloat(std::string_view uniformName, float value)
{
	glProgramUniform1f(m_programId, findUniformLocation(uniformName), value);
}

void Material::setInt(std::string_view uniformName, int value)
{
	glProgramUniform1i(m_programId, findUniformLocation(uniformName), value);
}

void Material::bindTextureUnit(int textureUnit, const Texture2D* texture) {
	if (texture)
		m_textures[textureUnit] = texture;
	else
		m_textures.erase(textureUnit);
}

void Material::use() const {
	glUseProgram(m_programId);
	for (const auto& pair : m_textures) {
		pair.second->bindToTextureUnit(pair.first);
	}
}

int Material::findUniformLocation(std::string_view name) const {
	return glGetUniformLocation(m_programId, name.data());
}

unsigned int Material::link() {
	unsigned int program{ glCreateProgram() };
	unsigned int vertexShader{ compileShader(GL_VERTEX_SHADER, m_vertexPath) };
	unsigned int fragmentShader{ compileShader(GL_FRAGMENT_SHADER, m_fragmentPath) };

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	int success{};
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		throw std::runtime_error{ static_cast<std::string>("Failed to link program! error info: ") + infoLog };
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

unsigned int Material::compileShader(GLEnum type, const char* path) {
	std::ifstream file{};
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::string code{};
	const char* codeArr{};
	try {
		file.open(path);

		std::stringstream stream{};
		stream << file.rdbuf();

		file.close();

		code = stream.str();
		codeArr = code.c_str();
	}
	catch (std::ifstream::failure) {
		throw std::runtime_error{ static_cast<std::string>("Error reading shader file: ") + path };
	}

	unsigned int shader{ glCreateShader(type) };
	glShaderSource(shader, 1, &codeArr, NULL);
	glCompileShader(shader);

	int success{};
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		throw std::runtime_error{ static_cast<std::string>("Failed to compile shader: ") + path + " | error info: " + infoLog };
	}

	return shader;
}