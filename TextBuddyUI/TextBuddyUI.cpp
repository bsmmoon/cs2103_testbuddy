#include "TextBuddyUI.h"


TextBuddyUI::TextBuddyUI() {
}

TextBuddyUI::~TextBuddyUI() {
}

int main(int argc, char* argv[]) {
	string fileName = TextBuddyLibrary::readFileName(argc, argv);

	TextBuddyMain buddy(fileName);
	buddy.run(fileName);

	return 0;
};
