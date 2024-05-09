#include "engine/Debug.h"

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