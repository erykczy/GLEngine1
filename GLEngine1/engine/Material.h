#pragma once
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <iostream>

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

	void use() {
		glUseProgram(m_programId);
	}

private:
	unsigned int m_programId{};
	const char* m_vertexPath{};
	const char* m_fragmentPath{};

	unsigned int link();

	unsigned int compileShader(GLenum type, const char* path);
};