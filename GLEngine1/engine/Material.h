#pragma once
#include <glm/mat4x4.hpp>

#include <map>
#include <string_view>

class Texture2D;
using GLEnum = unsigned int;

class Material final {
public:
	Material(const char* vertexPath, const char* fragmentPath);
	
	~Material();
	Material(const Material& source) : Material(source.m_vertexPath, source.m_fragmentPath) {}
	Material& operator=(const Material& source);
	Material(Material&& source) noexcept;
	Material& operator=(Material&& source) noexcept;

	void setSpaceTransformMatricies(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	void setMatrix4x4(std::string_view uniformName, glm::mat4 texture);
	void setTextureUnit(std::string_view uniformName, int textureUnit);
	void setTexture2D(int textureUnit, const Texture2D* texture);

	void use() const;

private:
	unsigned int m_programId{};
	const char* m_vertexPath{};
	const char* m_fragmentPath{};
	std::map<int, const Texture2D*> m_textures{};

	unsigned int link();

	unsigned int compileShader(GLEnum type, const char* path);

	int findUniformLocation(std::string_view name) const;
};