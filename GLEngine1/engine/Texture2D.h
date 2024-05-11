#pragma once

#include <string>

class Texture2D {
public:
	enum Format {
		rgb,
		rgba
	};

	Texture2D(std::string_view path, Format format = rgba);

	void bindToTextureUnit(int textureUnit) const;
	void unbindFromTextureUnit(int textureUnit) const;

	const std::string& getPath() const { return m_path; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	
private:
	std::string m_path{};
	int m_width{};
	int m_height{};

	unsigned int m_id{};
};