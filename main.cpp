#include "main.h"

void SwitchCommand(int USER_INPUT) {
	switch (USER_INPUT) {
	case 1:
		if (Utils::patch_dota_plus(false))
			LogSuccess("Dota Plus Unlocked\n")
		break;
	case 2:
		if (Utils::patch_dota_plus(true))
			LogSuccess("Dota Plus Reverted\n")
		break;
	default:
		DrawMenu();
		break;
	}
}

void DrawMenu() {
	Log("[1] Unlock Dota Plus\n")
	Log("[2] Revert Dota Plus\n")
	Log("\n>>> ")

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
