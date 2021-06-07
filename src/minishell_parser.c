/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 18:23:04 by lsuardi           #+#    #+#             */
/*   Updated: 2021/04/03 22:48:34 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*size_t	cmd_count(char **tokens)
{
	size_t	count;

	count = 1;
	while (*tokens)
	{
		if (**tokens ==  "|" || (**tokens == ";" && tokens[1]))
			count++;
		tokens++;
	}
	return (count);
}

t_cmd	**parser(char **tokens)
{
	const size_t	count = cmd_count(tokens);
	size_t			ac;
	t_cmd			**cmd_arr;
	int				i;
	int				j;
	bool			pipe;

	if (gb_alloc(&cmd_arr, sizeof(t_cmd *) * (count + 1)))
		return (NULL);
	cmd_arr[count] = NULL;
	i = -1;
	while (++i < count)
	{
		ac = arg_count(tokens);
		cmd_arr[i]->argc = ac;
		if (gb_alloc(tokens + i, sizeof(t_cmd) + ac * sizeof(char *)))
			return (NULL);
		j = 0;
		while (**tokens != "|" && **tokens != ";")
		{
			if (**tokens == ">" || **tokens == "<")
			{
				REDIRECTION;
				free(*tokens);
				*tokens = NULL;
			}
			else
				cmd_arr[i]->argv[j] = *tokens;
		}
		if (**tokens == "|")
			cmd_arr->pipe = true;
	}
}*/
