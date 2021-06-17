#include <minishell.h>

int	create_useless_files(t_list *out, const int stdfd[2])
{
	const t_list	*it = out->prev;

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
	if (current_cmd->redirect_out)
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

void	close_fdio(t_fdio fdio)
{
	if (fdio.in != -1)
		close(fdio.in);
	if (fdio.out != -1)
		close(fdio.out);
}
