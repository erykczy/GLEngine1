#pragma once
#include <string_view>
#include <iostream>
#include <string>

namespace Debug {
	inline void logInfo(std::string_view info) {
		std::cout << "INFO: " << info << '\n';
	}
}