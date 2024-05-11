#pragma once

#include "AppConstants.h"

#include <sstream>
#include <iomanip>

namespace glm {
	typedef vec<2, float, defaultp>	vec2;
	typedef vec<3, float, defaultp>	vec3;
	typedef vec<4, float, defaultp>	vec4;
}

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
		void setNumberPrecision(int precision) { m_numberPrecision = precision; }

	private:
		DebugType m_debugSensitivity{ endDebug };
		DebugType m_errorSensitivity{ endFatalError };
		std::stringstream m_message{};
		int m_numberPrecision{ AppConstants::defaultDebugNumberPrecision };

		std::string getTag(DebugType type);
	};

	template<typename T>
	Logger& Logger::operator<<(const T& data) {
		m_message << std::fixed << std::setprecision(m_numberPrecision) << data;
		return *this;
	}

	inline Logger logger{};

	void setWireframeRendering(bool wireframeRendering);
}

std::ostream& operator<<(std::ostream& out, const glm::vec2& vec);
std::ostream& operator<<(std::ostream& out, const glm::vec3& vec);
std::ostream& operator<<(std::ostream& out, const glm::vec4& vec);
