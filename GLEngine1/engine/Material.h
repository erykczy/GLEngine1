#pragma once
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <iostream>
#include "Texture2D.h"
#include <map>

class Material final {
public:
	Material(const char* vertexPath, const char* fragmentPath) : m_vertexPath(vertexPath), m_fragmentPath(fragmentPath) {
		m_programId = link();
	}
	
	~Material() {
		glDeleteProgram(m_programId);
	}
	Material(const Material& source) : Material(source.m_vertexPath, source.m_fragmentPath) {}
	Material& operator=(const Material& source) {
		if (&source == this) return *this;
		glDeleteProgram(m_programId);
		m_vertexPath = source.m_vertexPath;
		m_fragmentPath = source.m_fragmentPath;
		return *this;
	}
	Material(Material&& source) noexcept {
		m_programId = source.m_programId;
		m_vertexPath = source.m_vertexPath;
		m_fragmentPath = source.m_fragmentPath;

		source.m_programId = 0;
	}
	Material& operator=(Material&& source) noexcept {
		if (&source == this) return *this;
		glDeleteProgram(m_programId);

		m_programId = source.m_programId;
		m_vertexPath = source.m_vertexPath;
		m_fragmentPath = source.m_fragmentPath;

		source.m_programId = 0;
		return *this;
	}

	void setTextureUnit(std::string_view uniformName, int textureUnit) {
		glUniform1i(findUniformLocation(uniformName), textureUnit);
	}

	void setTexture2D(int textureUnit, const Texture2D* texture) {
		if (texture)
			m_textures[textureUnit] = texture;
		else
			m_textures.erase(textureUnit);
	}

	void use() const {
		glUseProgram(m_programId);
		for (const auto& pair : m_textures) {
			pair.second->bindToTextureUnit(pair.first);
		}
	}

private:
	unsigned int m_programId{};
	const char* m_vertexPath{};
	const char* m_fragmentPath{};
	std::map<int, const Texture2D*> m_textures{};

	unsigned int link();

	unsigned int compileShader(GLenum type, const char* path);

	GLint findUniformLocation(std::string_view name) const {
		return glGetUniformLocation(m_programId, name.data());
	}
};