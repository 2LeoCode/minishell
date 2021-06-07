#include <minishell.h>

void	minishell_exit(int ret)
{
	gb_load();
	gb_clear();
	save_history();
	tcsetattr(0, 0, &g_global_data.term_backup);
	exit(ret);
}
