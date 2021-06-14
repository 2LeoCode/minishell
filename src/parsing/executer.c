#include <minishell.h>
 
int	file_error(const char *path_to_file, const int stdfd[2])
{
	printf("minishell: %s: %s\n", strerror(errno), path_to_file);
	dup2(stdfd[0], 0);
	dup2(stdfd[1], 1);
	return (-2);
}

int	create_file(const char *path)
{
	int	fd;

	fd = open(path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}

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
	int		fd_test;
	char	*full_path;
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

void	close_fdio(t_fdio fdio)
{
	if (fdio.in != -1)
		close(fdio.in);
	if (fdio.out != -1)
		close(fdio.out);
}

pid_t	execute_cmd(t_shell *ms, t_cmd *current_cmd, t_fdio fdio, const int stdfd[2])
{
	pid_t			cpid;
	t_builtin_fun	builtin_fun;

	cpid = 0;
	builtin_fun = search_builtin(ms, *current_cmd->argv);
	if (fdio.in != -1)
		dup2(fdio.in, 0);
	if (fdio.out != -1)
		dup2(fdio.out, 1);
	if (builtin_fun)
		g_global_data.status = (*builtin_fun)(current_cmd->argc, current_cmd->argv, g_global_data.env->data);
	else
		cpid = run_executable(current_cmd, get_first_path(*current_cmd->argv));
	close_fdio(fdio);
	dup2(stdfd[0], 0);
	dup2(stdfd[1], 1);
	return (cpid);
}

void	do_pipe_child(t_shell *ms, t_cmd *current_cmd, t_executor exec)
{
	t_builtin_fun	builtin_fun;

	close(exec.pipefd[0]);
	if (exec.fdio.out != -1)
		dup2(exec.fdio.out, 1);
	else if (exec.fdio.pipe)
		dup2(exec.pipefd[1], 1);
	if (exec.fdio.in != -1)
		dup2(exec.fdio.in, 0);
	builtin_fun = search_builtin(ms, *current_cmd->argv);
	if (builtin_fun)
	{
		g_global_data.status = (*builtin_fun)(current_cmd->argc, current_cmd->argv, g_global_data.env->data);
		exit(EXIT_SUCCESS);
	}
	execve(exec.full_path, current_cmd->argv, g_global_data.env->data);
	perror("minishell");
	exit(EXIT_FAILURE);
}

int	cmd_fail(char *full_path)
{
	free(full_path);
	return (-1);
}

pid_t	execute_cmd_pipe(t_shell *ms, t_cmd *current_cmd, t_fdio fdio, const int stdfd[2])
{
	char			*full_path;
	t_executor		exec;
	int				pipefd[2];
	pid_t			cpid;

	cpid = 0;
	pipe(pipefd);
	full_path = get_first_path(*current_cmd->argv);
	if (!full_path)
		return (-1);
	exec = (t_executor){full_path, fdio, {pipefd[0], pipefd[1]}};
	cpid = fork();
	if (cpid == -1)
		return (cmd_fail(full_path));
	if (!cpid)
		do_pipe_child(ms, current_cmd, exec);
	close(pipefd[1]);
	if (fdio.in != -1)
		close(fdio.in);
	if (fdio.out != -1)
		close(fdio.out);
	dup2(pipefd[0], 0);
	dup2(stdfd[1], 1);
	free(full_path);
	return (cpid);
}

bool	check_error(pid_t *pid_value, char *executable_name)
{
	if (errno == ENOMEM)
		return (true);
	if (*pid_value == -1)
	{
		g_global_data.status = command_error(executable_name);
		*pid_value = 0;
	}
	return (false);
}

int	create_useless_files(t_list *out, const int stdfd[2])
{
	const t_list *it = out->prev;

	while (it->prev != out)
	{
		if (create_file(it->data))
			return (file_error(it->data, stdfd));
		it = it->prev;
	}
	return (0);
}

int	open_useful_files(t_cmd *current_cmd, t_fdio *fdio, const int stdfd[2])
{
	if (current_cmd->in)
		fdio->in = open(current_cmd->in, O_RDONLY);
	if (lst_size(current_cmd->redirect_out))
	{
		fdio->out = open(current_cmd->out->next->data,
			O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fdio->out == -1)
			return (file_error(current_cmd->out->next->data, stdfd));
	}
	else if (current_cmd->redirect_out2)
	{
		fdio->out = open(current_cmd->out->next->data,
			O_CREAT | O_WRONLY | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fdio->out == -1)
			return (file_error(current_cmd->out->next->data, stdfd));
	}
	return (0);
}

void	init_fdio(t_fdio *fdio, t_cmd *current_cmd)
{
	fdio->in = -1;
	fdio->out = -1;
	fdio->pipe = current_cmd->pipe;
}

void	wait_if_child_running(pid_t cpid)
{
	if (cpid)
	{
		waitpid(cpid, &g_global_data.status, 0);
		cpid = 0;
	}
}

int	executer(t_shell *ms, t_cmd **cmd_arr)
{
	pid_t		cpid;
	t_fdio		fdio;
	const int	stdfd[2] = {dup(0), dup(1)};

	cpid = 0;
	while (*cmd_arr)
	{
		init_fdio(&fdio, *cmd_arr);
		if (create_useless_files((*cmd_arr)->out, stdfd)
					|| open_useful_files(*cmd_arr, &fdio, stdfd))
			return (-1);
		wait_if_child_running(cpid);
		if (!(*cmd_arr)->pipe)
			cpid = execute_cmd(ms, *cmd_arr, fdio, stdfd);
		else
			cpid = execute_cmd_pipe(ms, *cmd_arr, fdio, stdfd);
		if (check_error(&cpid, *(*cmd_arr)->argv))
			return (-1);
		cmd_arr++;
	}
	if (cpid)
		waitpid(cpid, &g_global_data.status, 0);
	return (0);
}
