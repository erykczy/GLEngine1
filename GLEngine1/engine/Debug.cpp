#include "engine/Debug.h"

#include <iostream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Debug {
	Logger& Logger::operator<<(DebugType type) {
		if (type >= m_errorSensitivity) {
			throw std::runtime_error{ getTag(type) + ": " + m_message.str()};
		}
		else if(type >= m_debugSensitivity) {
			std::cout << getTag(type) << ": " << m_message.str() << '\n';
		}
		m_message.str(std::string{});
		return *this;
	}

	std::string Logger::getTag(DebugType type) {
		switch (type)
		{
		case endDebug: return "debug";
		case endInfo: return "INFO";
		case endWarning: return "=> WARNING";
		case endError: return "===> ERROR";
		case endFatalError: return "======> FATAL ERROR";
		default: return "???";
		}
	}

	void Logger::setDebugSensitivity(DebugType type) {
		if (m_debugSensitivity < 0) Debug::logger << "Invalid debug type!" << Debug::endError;
		m_debugSensitivity = type;
	}
	
	void Logger::setErrorSensitivity(DebugType type) {
		if (m_debugSensitivity < 0) Debug::logger << "Invalid debug type!" << Debug::endError;
		m_errorSensitivity = type;
	}
}

std::ostream& operator<<(std::ostream& out, const glm::vec2& vec) {
	out << "(" << vec.x << ", " << vec.y << ")";
	return out;
}

std::ostream& operator<<(std::ostream& out, const glm::vec3& vec) {
	out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return out;
}

std::ostream& operator<<(std::ostream& out, const glm::vec4& vec) {
	out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
	return out;
}