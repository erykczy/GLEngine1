#pragma once

#include "engine/Scene.h"

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

	void applySceneData(Scene* scene);
	void setSpaceTransformMatricies(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void setMatrix4x4(std::string_view uniformName, const glm::mat4& matrix);
	void setVector3(std::string_view uniformName, const glm::vec3& vec);
	void setVector4(std::string_view uniformName, const glm::vec4& vec);
	void setFloat(std::string_view uniformName, float value);
	void setInt(std::string_view uniformName, int value);
	void setTextureUnit(std::string_view uniformName, int textureUnit);

	void bindTextureUnit(int textureUnit, const Texture2D* texture);

	void use() const;

private:
	unsigned int m_programId{};
	const char* m_vertexPath{};
	const char* m_fragmentPath{};
	std::map<int, const Texture2D*> m_textures{};

	unsigned int link();

	unsigned int compileShader(GLEnum type, const char* path);

	int findUniformLocation(std::string_view name) const;

	void applyLighting(Scene* scene);
};