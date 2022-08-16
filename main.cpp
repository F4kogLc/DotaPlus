#include "main.h"
#include <string>

void SwitchCommand(int USER_INPUT) {
	switch (USER_INPUT) {
	case 1:
		if (Utils::patch_dota_plus(false))
			std::cout << "[+] Dota Plus Unlocked" << std::endl;
		break;
	case 2:
		if (Utils::patch_dota_plus(true))
			std::cout << "[+] Dota Plus Reverted" << std::endl;
		break;
	default:
		DrawMenu();
		break;
	}
}

void DrawMenu() {
	std::cout << "[1] Unlock Dota Plus" << std::endl;
	std::cout << "[2] Lock Dota Plus" << std::endl;
	std::cout << "\n>>> ";

	int USER_INPUT;
	std::cin >> USER_INPUT;
	SwitchCommand(USER_INPUT);
}

int main() {

    if (!Utils::get_dota_path(&Globals::dota_path)) {
        system("pause");
        return 0;
    }

    DrawMenu();

    system("pause");
    return 0;
}
