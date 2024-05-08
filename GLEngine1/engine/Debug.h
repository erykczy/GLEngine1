#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <string_view>
#include <iostream>
#include <string>
#include <ostream>

namespace Debug {
	enum DebugType {
		debug,
		info,
		warning
	};

	inline DebugType debugSensitivity{ debug };

	inline std::string_view getTag(DebugType type) {
		switch (type)
		{
		case Debug::debug: return "DEBUG";
		case Debug::info: return "=> INFO";
		case Debug::warning: return "===> WARNING";
		default: return "???";
		}
	}

	inline void log(DebugType type, std::string_view info) {
		if (type < debugSensitivity) return;
		std::cout << getTag(type) << ": " << info << '\n';
	}
}

inline std::ostream& operator<<(std::ostream& out, const glm::vec2 vec) {
	out << "(" << vec.x << ", " << vec.y << ")";
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const glm::vec3 vec) {
	out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const glm::vec4 vec) {
	out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
	return out;
}