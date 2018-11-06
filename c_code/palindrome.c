#include <stdio.h>
#include <string.h>

int main() {

	char text[] = "Fuckin Son of Bitch, C sucks ass!!ssa skcus C ,hctiB fo noS nikcuF";
	char True[] = "True! '%s' is a palindrome.%c";
	char False[] = "False! '%s' is not a palindrome.%c";

	int i;
	int l = strlen(text);
	int lh = l / 2;
	int rst = 1;
	for (i = 0; i < lh; i += 1) {
		if (text[i] != text[l-1-i]) {
			rst = 0;
			break;
		}
	}

	if (rst == 1) {
		printf(True, text, 10);
	} else {
		printf(False, text, 10);
	}
	return 0;
}
