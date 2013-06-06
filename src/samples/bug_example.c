#include "../misc.h"

#define DEBUG 1

int main() {
	char* msg = "This is a DEBUG MESSAGE!";
	BUG("debug message: %s", msg);

	BUG_("debug message with getch");

	BUG_PRINT("This debug message does not print function name, line number and file before printing message: %s\n", msg);

	BUG_PRINT_("And this message is the same as previous one, but it uses getch()\n");

	BUG_PRINT("\nif DEBUG is not defined, calling BUG*(\"stuff\") will do nothing!\n\n\n");
}
