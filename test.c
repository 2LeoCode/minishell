#include <stdio.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>

int main(void) {
	struct termios current, backup;

	if ((tcgetattr(0, &current) == -1)
		|| (tcgetattr(0, &backup) == -1))
		return (-1);
	current.c_lflag &= ~(ICANON);
	current.c_lflag &= ~(ECHO);
	if (tcsetattr(0, 0, &current) == -1)
	{
		write(2, "Error while setting terminal in non-cannonical mode\n", 52);
		return (-1);
	}
	tcsetattr(0, 0, &backup);
	return 0;
}
