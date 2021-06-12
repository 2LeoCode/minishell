#include <minishell.h>

int	create_file(const char *path)
{
	int	fd;

	fd = open(path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	close(fd);
}

/*t_builtin_fun	search_builtin(t_shell *ms, char *name)
{
	const size_t	name_len = ft_strlen(name);
	unsigned int	i;
	
	i = 0;
	while (i < BUILTIN_COUNT && ft_memcmp(ms->builtin_fct_name[i], name, name_len))
		i++;
	if (i == BUILTIN_COUNT)
		return (NULL);
	return (ms->builtin_fct_ptr[i]);
}*/

char	*get_first_path(char *executable_name, char **path)
{
	int		fd_test;
	char	*full_path;

	while (*path)
	{
		full_path = ft_strcjoin(*path, executable_name, '/');
		fd_test = open(full_path, O_RDONLY);
		if (fd_test != -1)
			return (full_path);
		free(full_path);
		path++;
	}
	return (NULL);
}

pid_t	execute_cmd(t_shell *ms, t_cmd *current_cmd, t_fdio fdio, char **path)
{
	pid_t			cpid;
	t_builtin_fun	builtin_fun;
	char			*full_path;

	cpid = 0;
	builtin_fun = NULL;(void)ms;//search_builtin(ms, *current_cmd->argv);
	if (fdio.in != -1)
		dup2(fdio.in, 0);
	if (fdio.out != -1)
		dup2(fdio.out, 1);
	if (builtin_fun)
		g_global_data.status = (*builtin_fun)(current_cmd->argc, current_cmd->argv, g_global_data.env->data);
	else
	{
		full_path = get_first_path(*current_cmd->argv, path);
		if (!full_path)
			return (-1);
		cpid = fork();
		if (cpid == -1)
			return (-1);
		if (!cpid)
		{
			execve(full_path, current_cmd->argv, g_global_data.env->data);
			perror("minishell");
		}
		free(full_path);
	}
	if (fdio.in != -1)
		close(fdio.in);
	if (fdio.out != -1)
		close(fdio.out);
	return (cpid);
}

pid_t	execute_cmd_pipe(t_shell *ms, t_cmd *current_cmd, t_fdio fdio, char **path)
{
	t_builtin_fun	builtin_fun;
	char			*full_path;
	int				pipefd[2];
	pid_t			cpid;

	cpid = 0;
	pipe(pipefd);
	full_path = get_first_path(*current_cmd->argv, path);
	if (!full_path)
		return (-1);
	cpid = fork();
	if (cpid == -1)
	{
		ft_destroy_array((void **)path, NULL_ENDED);
		return (-1);
	}
	if (!cpid)
	{
		close(pipefd[0]);
		if (fdio.out != -1)
			dup2(fdio.out, 1);
		else
			dup2(pipefd[1], 1);
		if (fdio.in != -1)
			dup2(fdio.in, 0);
		builtin_fun = NULL;(void)ms;//search_builtin(ms, *current_cmd->argv);
		if (builtin_fun)
		{
			g_global_data.status = (*builtin_fun)(current_cmd->argc, current_cmd->argv, g_global_data.env->data);
			exit(EXIT_SUCCESS);
		}
		execve(full_path, current_cmd->argv, g_global_data.env->data);
		perror("minishell");
	}
	close(pipefd[1]);
	if (fdio.in != -1)
		close(fdio.in);
	if (fdio.out != -1)
		close(fdio.out);
	dup2(pipefd[0], 0);
	free(full_path);
	return (cpid);
}

bool	check_error(pid_t *pid_value, char *executable_name, char **path)
{
	if (errno == ENOMEM)
	{
		ft_destroy_array((void **)path, NULL_ENDED);
		return (true);
	}
	if (*pid_value == -1)
	{
		g_global_data.status = command_error(executable_name);
		*pid_value = 0;
	}
	return (false);
}

int	executer(t_shell *ms, t_cmd **cmd_arr)
{
	char		**path;
	pid_t		cpid;
	t_fdio		fdio;
	t_list		*it;
	const int	stdfd[2] = {dup(0), dup(1)};

	path = ft_split(ft_getenv("PATH"), ':');
	if (!path)
		return (-1);
	cpid = 0;
	while (*cmd_arr)
	{
		fdio.out = -1;
		fdio.in = -1;
		if ((*cmd_arr)->in)
			fdio.in = open((*cmd_arr)->in, O_RDONLY);
		it = (*cmd_arr)->out->prev;
		while (it->prev != (*cmd_arr)->out)
		{
			create_file(it->data);
			it = it->prev;
		}
		if ((*cmd_arr)->redirect_out)
			fdio.out = open((*cmd_arr)->out->next->data,
				O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if ((*cmd_arr)->redirect_out2)
			fdio.out = open((*cmd_arr)->out->next->data,
				O_CREAT | O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (cpid)
		{
			waitpid(cpid, &g_global_data.status, 0);
			cpid = 0;
		}
		if (!(*cmd_arr)->pipe)
		{
			cpid = execute_cmd(ms, *cmd_arr, fdio, path);
			dup2(stdfd[0], 0);
			dup2(stdfd[1], 1);
		}
		else
		{
			cpid = execute_cmd_pipe(ms, *cmd_arr, fdio, path);
			dup2(stdfd[1], 1);
		}
		if (check_error(&cpid, *(*cmd_arr)->argv, path))
			return (-1);
		cmd_arr++;
	}
	if (cpid)
		waitpid(cpid, &g_global_data.status, 0);
	ft_destroy_array((void **)path, NULL_ENDED);
	return (0);
}
