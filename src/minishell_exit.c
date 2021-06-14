#include <minishell.h>

void	minishell_exit(int ret)
{
	pre_exit_clear();
	save_history();
	tcsetattr(0, 0, &g_global_data.term_backup);
	minishell_clear();
	exit(ret);
}
