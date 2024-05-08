#pragma once
#include <string_view>
#include <iostream>
#include <string>

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