#include "engine/Texture2D.h"

#include "libraries/stb_image.h"

#include <glad/glad.h>

#include <string>
#include <stdexcept>

Texture2D::Texture2D(std::string_view path, Format format) : m_path{ path } {
	// create texture object
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	// texture settings
	// TODO make these settings modifiable
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// load texture from path
	int nrChannels;
	unsigned char* data{ stbi_load(path.data(), &m_width, &m_height, &nrChannels, 0) };
	if (!data) throw std::runtime_error(static_cast<std::string>("Failed to load texture: ") + path.data());

	// set texture data
	auto texFormat = format == rgb ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, texFormat, m_width, m_height, 0, texFormat, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);

	// generate mimaps
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2D::bindToTextureUnit(int textureUnit) const {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture2D::unbindFromTextureUnit(int textureUnit) const {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
}