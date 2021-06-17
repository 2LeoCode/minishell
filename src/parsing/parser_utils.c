#include <minishell.h>

void	destroy_cmd_array(t_cmd **cmd_arr)
{
	t_cmd	**it;
	int		i;

	it = cmd_arr - 1;
	while (*++it)
	{
		lst_destroy((*it)->out);
		free((*it)->in);
		i = -1;
		while (++i < (*it)->argc)
			free((*it)->argv[i]);
		free(*it);
	}
	free(cmd_arr);
}

void	*parser_failure(char **tokens, size_t token_cnt, t_cmd **cmd_arr)
{
	destroy_cmd_array(cmd_arr);
	ft_destroy_array((void **)tokens, token_cnt);
	return (NULL);
}

size_t	cmd_count(char **tokens)
{
	size_t	count;

	count = 1;
	while (*tokens)
	{
		if (**tokens == '|' || (**tokens == ';' && tokens[1]))
			count++;
		tokens++;
	}
	return (count);
}

int	arg_count(char **tokens)
{
	int	count;

	count = 0;
	while (*tokens && **tokens != '|' && **tokens != ';')
	{
		if (**tokens == '>' || **tokens == '<')
			tokens++;
		else
			count++;
		tokens++;
	}
	return (count);
}

bool	is_valid_file(char *path)
{
	int	test_fd;

	test_fd = open(path, O_RDONLY);
	if (test_fd == -1)
		return (false);
	close(test_fd);
	return (true);
}
