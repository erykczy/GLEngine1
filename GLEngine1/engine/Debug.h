#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <string_view>
#include <iostream>
#include <sstream>

namespace Debug {
	enum DebugType {
		endDebug,
		endInfo,
		endWarning,
		endError,
		endFatalError
	};
	
	class Logger final {
	public:
		template<typename T>
		Logger& operator<<(const T& data);
		Logger& operator<<(DebugType type);

		DebugType getDebugSensitivity() const { return m_debugSensitivity; }
		DebugType getErrorSensitivity() const { return m_errorSensitivity; }
		void setDebugSensitivity(DebugType type);
		void setErrorSensitivity(DebugType type);

	private:
		DebugType m_debugSensitivity{ endDebug };
		DebugType m_errorSensitivity{ endError };
		std::stringstream m_message{};

		std::string getTag(DebugType type);
	};

	template<typename T>
	Logger& Logger::operator<<(const T& data) {
		m_message << data;
		return *this;
	}

	inline Logger logger{};
}

inline std::ostream& operator<<(std::ostream& out, const glm::vec2& vec) {
	out << "(" << vec.x << ", " << vec.y << ")";
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const glm::vec3& vec) {
	out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const glm::vec4& vec) {
	out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
	return out;
}