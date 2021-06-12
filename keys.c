#include "inc/libft.h"
#include <termios.h>
#include <stdio.h>

# define _KEY_ESC 27

int main(void)
{
	struct termios	backup, current;
	int				key;

	tcgetattr(0, &backup);
	tcgetattr(0, &current);
	current.c_lflag &= ~(ICANON);
	current.c_lflag &= ~(ECHO);
	tcsetattr(0, 0, &current);
	while ((key = ft_getchar()) != _KEY_ESC)
		printf("%d\n", key);
	tcsetattr(0, 0,  &backup);
	return (0);
}
