#include "main.h"
#include <fstream>
#include <regex>

bool Utils::get_dota_path_from_reg(std::string* path) {
    HKEY h_key{};
    if (int error = RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Classes\\dota2\\Shell\\Open\\Command", 0, KEY_QUERY_VALUE, &h_key) != ERROR_SUCCESS) {
        std::cout << "[-] Registry Read Failed at RegOpenKey, Error: " << error << std::endl;
        RegCloseKey(h_key);
        return false;
    }

    char dota_path_reg[MAX_PATH]{};
    dota_path_reg[0] = '"';
    DWORD dota_path_size = sizeof(dota_path_reg) - sizeof(char);

    if (int error = RegQueryValueExA(h_key, nullptr, nullptr, nullptr, (LPBYTE)(dota_path_reg + 1), &dota_path_size) != ERROR_SUCCESS) {
        std::cout << "[-] Registry Read Failed at RegQueryValue, Error: " << error << std::endl;
        RegCloseKey(h_key);
        return false;
    }

    RegCloseKey(h_key);
    *path = dota_path_reg;

    return true;
}

bool Utils::get_dota_path(std::string* path) {
    std::string dota_path;
    if (!get_dota_path_from_reg(&dota_path)) {
        return false;
    }

    std::regex rgx{ R"(([^]:\\[^]+\\game\\))" };
    std::smatch matches;

    if (!std::regex_search(dota_path, matches, rgx)) {
        std::cout << "[-] Failed to parse Dota path!" << std::endl;
        return false;
    }

    *path = matches[1].str();

    return true;
}

int Utils::find_offset(char* array, int array_length, BYTE* pattern, int pattern_length) {
    for (int haystack_index = 0; haystack_index < array_length; haystack_index++) {
        bool needle_found = true;
        for (size_t needle_index = 0; needle_index < pattern_length; needle_index++) {
            char haystack_character = array[haystack_index + needle_index];
            char needle_character = pattern[needle_index];
            if (needle_character == 0x00 || haystack_character == needle_character)
                continue;
            else {
                needle_found = false;
                break;
            }
        }
        if (needle_found)
            return haystack_index;
    }

    return 0;
}

bool Utils::get_byte_array(std::string file_path, char** ret_array, int* file_size) {
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    int file_length = static_cast<int>(file.tellg());
    if (file_length == 0) {
        std::cout << "[-] File Size is NULL!" << std::endl;
        return false;
    }

    char* array = new char[file_length];
    file.rdbuf()->pubseekoff(0, std::ios_base::beg);
    file.read(array, file_length);
    file.close();

    *file_size = file_length;
    *ret_array = array;

    return true;
}

int Utils::find_offset(std::string file_path, BYTE* pattern, int pattern_size) {
    char* array = nullptr;
    int file_size = 0;

    if (!get_byte_array(file_path, &array, &file_size))
        return 0;

    int patch_offset = find_offset(array, file_size, pattern, pattern_size);

    return patch_offset;
}

void Utils::apply_patch(std::string file_path, int patch_offset, BYTE replace[], int bytes_to_replace) {
    FILE* pFile;
    fopen_s(&pFile, file_path.c_str(), "r+b");

    for (int i = 0; i < bytes_to_replace; i++) {
        fseek(pFile, patch_offset + i, SEEK_SET);
        fputc(replace[i], pFile);
    }

    fclose(pFile);
}

bool Utils::patch_dota_plus(bool revert) {
    std::string client_path = Globals::dota_path + "dota\\bin\\win64\\client.dll";

    BYTE Replace[] = { 0x70 };
    if (revert) {
        Globals::dota_plus_pattern[7] = { 0x70 };
        Replace[0] = 0x58;
    }

    int dota_plus_patch_offset = Utils::find_offset(client_path, Globals::dota_plus_pattern, sizeof(Globals::dota_plus_pattern));
    if (!dota_plus_patch_offset) {
        std::cout << "[-] Dota Plus Unlock Offset is NULL!" << std::endl;
        return false;
    }

    Utils::apply_patch(client_path, dota_plus_patch_offset + 7, Replace, sizeof(Replace));

    return true;
}