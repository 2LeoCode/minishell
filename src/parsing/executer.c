#include <minishell.h>

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
		g_global_data.status = (*builtin_fun)(current_cmd->argc,
				current_cmd->argv, g_global_data.env->data);
		free(exec.full_path);
		pre_exit_clear();
		minishell_clear();
		exit(EXIT_SUCCESS);
	}
	execve(exec.full_path, current_cmd->argv, g_global_data.env->data);
	perror("minishell");
	exit(EXIT_FAILURE);
}

static pid_t	execute_cmd(t_shell *ms, t_cmd *current_cmd, t_fdio fdio,
	const int stdfd[2])
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
		g_global_data.status = (*builtin_fun)(current_cmd->argc,
				current_cmd->argv, g_global_data.env->data);
	else
		cpid = run_executable(current_cmd, get_first_path(*current_cmd->argv));
	g_global_data.current_cpid = cpid;
	close_fdio(fdio);
	dup2(stdfd[0], 0);
	dup2(stdfd[1], 1);
	return (cpid);
}

static pid_t	execute_cmd_pipe(t_shell *ms, t_cmd *current_cmd, t_fdio fdio,
	const int stdfd[2])
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
	cpid = fork_and_do_child(ms, current_cmd, exec);
	if (cpid == -1)
		return (cmd_fail(full_path));
	g_global_data.current_cpid = cpid;
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

static void	wait_if_child_running(pid_t *cpid)
{
	if (*cpid)
	{
		waitpid(*cpid, &g_global_data.status, 0);
		*cpid = 0;
		g_global_data.current_cpid = 0;
	}
}

int	executer(t_shell *ms, t_cmd **cmd_arr)
{
	pid_t		cpid;
	t_fdio		fdio;
	const int	stdfd[2] = {dup(0), dup(1)};

	cpid = 0;
	cmd_arr--;
	while (*++cmd_arr)
	{
		init_fdio(&fdio, *cmd_arr);
		if (create_useless_files((*cmd_arr)->out, stdfd)
			|| open_useful_files(*cmd_arr, &fdio, stdfd))
			return (-1);
		wait_if_child_running(&cpid);
		if (!(*cmd_arr)->argc)
			continue ;
		if (!(*cmd_arr)->pipe)
			cpid = execute_cmd(ms, *cmd_arr, fdio, stdfd);
		else
			cpid = execute_cmd_pipe(ms, *cmd_arr, fdio, stdfd);
		if (check_error(&cpid, *(*cmd_arr)->argv))
			return (-1);
	}
	wait_if_child_running(&cpid);
	return (0);
}
