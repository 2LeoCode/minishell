#include <minishell.h>

void	kek(void)
{
	ft_putendl("kek");
}

int	builtin_env(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	while (*envp)
	{
		ft_putendl(*envp);
		envp++;
	}
	return (0);
}
