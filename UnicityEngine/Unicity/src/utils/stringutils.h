#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace u_engine {

	static std::vector<UE_string> split_string(const UE_string &s, UE_char delimeter) {
		std::vector<UE_string> elems;
		std::stringstream ss(s);
		UE_string item;
		while (std::getline(ss, item, delimeter)) {
			elems.push_back(item);
		}
		return elems;
	}

}