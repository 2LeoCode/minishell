#include <minishell.h>

void	set_terminal_attributes(void)
{
	if (tcsetattr(0, 0, &g_global_data.term_current) == -1)
	{
		minishell_error();
		minishell_exit(-1);
	}
}

void	reset_terminal_attributes(void)
{
	if (tcsetattr(0, 0, &g_global_data.term_backup) == -1)
	{
		minishell_error();
		minishell_exit(-1);
	}
}

/*
**	In this function we will get the current terminal attributes into two
**	`struct `, one that we edit through bit mask to remove the ICANON
**	(canonical-termiosmode) and ECHO (echo-mode) and apply to our current terminal
**	through `tcsetattr`, and one that we will keep as a backup to reset the
**	terminal to how it was before at the end of the program.
**	The non-canonical mode will make the `read` function non-blocking, so every
**	key will be returned immediately without waiting for a new line like by
**	default.
**	And the echo mode just means that when you press a key it will echo it on
**	the terminal, so disabling it will just send the key to the program without
**	echoing it, so we will have to print it manually with `write`, this will
**	allow us to move our cursor and insert/delete characters in the middle of
**	our input.
*/
int	setup_termios(void)
{
	if ((tcgetattr(0, &g_global_data.term_current) == -1)
		|| (tcgetattr(0, &g_global_data.term_backup) == -1))
		return (-1);
	g_global_data.term_current.c_lflag &= ~(ICANON);
	g_global_data.term_current.c_lflag &= ~(ECHO);
	if (tcsetattr(0, 0, &g_global_data.term_current) == -1)
	{
		write(2, "Error while editing terminal attributes\n", 40);
		return (-1);
	}
	return (0);
}

/*
**	Here we simply initialize the termcap library and pick up the termcaps that
**	we will need in the program into our `t_term` struct.
*/
int	setup_termcaps(t_term *tc)
{
	int				ret;
	char			*term_name;

	term_name = ft_getenv("TERM");
	if (!term_name)
		write(2, "Specify a terminal type with 'TERM=<type>'.\n", 44);
	else
	{
		ret = tgetent(NULL, term_name);
		if (!ret)
			write(2, "Your terminal is not defined in termcap database"
				" (or too little information).\n", 78);
		else if (ret == -1)
			write(2, "Could not access the termcap database.\n", 39);
	}
	if (!term_name || (ret != 1))
		return (-1);
	tc->le = tgetstr("le", NULL);
	tc->ri = tgetstr("nd", NULL);
	tc->ks = "\033[0K";
	tc->ile = tgetstr("LE", NULL);
	return (0);
}
