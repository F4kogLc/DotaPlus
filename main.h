#pragma once
#include <Windows.h>
#include <iostream>

void SwitchCommand(int USER_INPUT);
void DrawMenu();

namespace Utils {
	bool get_dota_path_from_reg(std::string* path);
	bool get_dota_path(std::string* path);

	int find_offset(char* array, int array_length, BYTE* pattern, int pattern_length);
	int find_offset(std::string file_path, BYTE* pattern, int pattern_size);
	bool get_byte_array(std::string file_path, char** ret_array, int* file_size);
	void apply_patch(std::string file_path, int patch_offset, BYTE replace[], int bytes_to_replace);

	bool patch_dota_plus(bool revert);
}

namespace Globals {
	inline std::string dota_path;

	inline BYTE dota_plus_pattern[] = { 0xBF, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x48, 0x58, 0x85, 0xC9, 0x0F, 0x85 };
}
