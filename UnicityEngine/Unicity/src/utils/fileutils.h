#pragma once
#include <string>
#include <fstream>
#include <iostream>

namespace u_engine {

	static UE_string read_file(const UE_char* filepath) {
	
		FILE* file = fopen(filepath, "rt");
		if (file != NULL) {

			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			UE_char* data = new UE_char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			UE_string result(data);
			delete[] data;
			return result;
			}
			
		}
	
	
}