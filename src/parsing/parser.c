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

static size_t	cmd_count(char **tokens)
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

static int	arg_count(char **tokens)
{
	int	count;

	count = 1;
	while (*tokens && **tokens != '|' && **tokens != ';')
	{
		if (*tokens == '>' || *tokens == '<')
			tokens++;
		else
			count++;
		tokens++;
	}
	return (count);
}

static int	parse_token(char ***token_ptr, t_cmd *current_cmd)
{
	if (***token_ptr == '>')
	{
		current_cmd->redirect_out = !**token_ptr[1];
		current_cmd->redirect_out2 = **token_ptr[1];
		free(**token_ptr);
		*((*token_ptr)++) = NULL;
		if (lst_push_front(current_cmd->out, **token_ptr))
			return (-1);
		free(**token_ptr);
	}
	else if (***token_ptr == '<')
	{
		current_cmd->redirect_in = true;
		if (current_cmd->in)
		{
			free(current_cmd->in);
			current_cmd->in = *(++(*token_ptr));
		}
	}
	else
		current_cmd->argv[j++] = **token_ptr;
	return (0);
}

static int	parse_command(char ***token_ptr, t_cmd *current_cmd)
{
	unsigned int	j;

	j = 0;
	while (***token_ptr != '|' && ***token_ptr != ';')
	{
		if (parse_token(token_ptr, current_cmd))
			return (-1);
		(*token_ptr)++;
	}
	if (***token_ptr == '|')
		current_cmd->pipe = true;
}

t_cmd	**parser(char **tokens)
{
	const size_t	count = cmd_count(tokens);
	size_t			ac;
	t_cmd			**cmd_arr;
	int				i;

	gb_save();
	if (gb_alloc(&cmd_arr, sizeof(t_cmd *) * (count + 1)))
		return (NULL);
	cmd_arr[count] = NULL;
	i = -1;
	while (++i < count)
	{
		ac = arg_count(tokens);
		if (gb_alloc(&cmd_arr[i], sizeof(t_cmd) + ac * sizeof(char *))
					|| lst_init(&cmd_arr[i]->out))
			return (NULL);
		gb_add(cmd_arr[i]->out, lst_destroy);
		cmd_arr[i]->in = NULL;
		cmd_arr[i]->argc = ac;
		if (parse_command(&tokens))
			return (NULL);
	}
	return (cmd_arr);
}
