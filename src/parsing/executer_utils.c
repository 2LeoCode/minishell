#include <minishell.h>

t_builtin_fun	search_builtin(t_shell *ms, char *name)
{
	unsigned int	i;

	i = 0;
	while (i < BUILTIN_COUNT && ft_strcmp(ms->builtin_fct_name[i], name))
		i++;
	if (i == BUILTIN_COUNT)
		return (NULL);
	return (ms->builtin_fct_ptr[i]);
}

char	*get_first_path(char *executable_name)
{
	int			fd_test;
	char		*full_path;
	const char	**it = (const char **)g_global_data.path;

	full_path = ft_strdup(executable_name);
	if (!full_path)
		return (NULL);
	fd_test = open(full_path, O_RDONLY);
	close(fd_test);
	if (fd_test != -1)
		return (full_path);
	free(full_path);
	while (*it)
	{
		full_path = ft_strcjoin(*it, executable_name, '/');
		fd_test = open(full_path, O_RDONLY);
		close(fd_test);
		if (fd_test != -1)
			return (full_path);
		free(full_path);
		it++;
	}
	return (NULL);
}

pid_t	run_executable(t_cmd *current_cmd, char *full_path)
{
	pid_t	cpid;

	if (!full_path)
		return (-1);
	cpid = fork();
	if (cpid == -1)
	{
		free(full_path);
		return (-1);
	}
	if (!cpid)
	{
		execve(full_path, current_cmd->argv, g_global_data.env->data);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	free(full_path);
	return (cpid);
}

int	cmd_fail(char *full_path)
{
	free(full_path);
	return (-1);
}

pid_t	fork_and_do_child(t_shell *ms, t_cmd *current_cmd, t_executor exec)
{
	pid_t	cpid;

	cpid = fork();
	if (!cpid)
		do_pipe_child(ms, current_cmd, exec);
	return (cpid);
}
