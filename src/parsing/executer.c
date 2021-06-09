#include <minishell.h>

void	create_file(const char *path)
{
	int	fd;

	fd = open(path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	close(fd);
}

int	executer(t_shell *ms, t_cmd **cmd_arr)
{
	int		pipefd[2];
	pid_t	cpid;
	int		in_fd;
	int		out_fd;
	t_list	*it;

	while (*cmd_arr)
	{
		out_fd = 0;
		in_fd = 0;
		pipe(pipefd);
		if ((*cmd_arr)->in)
			in_fd = open((*cmd_arr)->in, O_RDONLY);
		it = (*cmd_arr)->out->prev;
		while (it->prev != (*cmd_arr)->out)
			create_file(it->data);
		if ((*cmd_arr)->redirect_out)
			out_fd = open((*cmd_arr)->out->next->data,
				O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if ((*cmd_arr)->redirect_out2)
			out_fd = open((*cmd_arr)->out->next->data,
				O_CREAT | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (!(*cmd_arr)->pipe)
		{
			EXECUTE_COMMAND
		}
		else PIPE/FORK EXECUTE
	}
	return (0);
}
