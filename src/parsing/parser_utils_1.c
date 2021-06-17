#include <minishell.h>

static int	remove_quotes(char **s_ptr)
{
	char	*new_s;

	new_s = ft_strntrim(*s_ptr, "\"\'", 1);
	if (!new_s)
		return (-1);
	free(*s_ptr);
	*s_ptr = new_s;
	return (0);
}

t_cmd	**cmd_arr_without_quotes(t_cmd **cmd_arr)
{
	int	i;
	int	j;

	i = -1;
	while (cmd_arr[++i])
	{
		j = -1;
		while (++j < cmd_arr[i]->argc)
		{
			if ((*cmd_arr[i]->argv[j] == '\'' || *cmd_arr[i]->argv[j] == '\"')
				&& remove_quotes(&cmd_arr[i]->argv[j]))
			{
				destroy_cmd_array(cmd_arr);
				return (NULL);
			}
		}
	}
	return (cmd_arr);
}
