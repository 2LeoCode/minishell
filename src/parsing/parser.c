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

static void		*parser_failure(char **tokens)
{
	ft_destroy_array((void **)tokens, NULL_ENDED);
	return (NULL);
}

static size_t	cmd_count(char **tokens)
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

static int	arg_count(char **tokens)
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

static char	**parse_token(char **token, t_cmd *current_cmd, unsigned int *index)
{
	if (**token == '>')
	{
		current_cmd->redirect_out = !(*token)[1];
		current_cmd->redirect_out2 = (*token)[1];
		free(*token);
		*token++ = NULL;
		if (lst_push_front(current_cmd->out, *token, ft_strlen(*token) + 1))
			return (NULL);
		free(*token);
		*token = NULL;
	}
	else if (**token == '<')
	{
		current_cmd->redirect_in = true;
		current_cmd->in = *++token;
	}
	else
		current_cmd->argv[(*index)++] = *token;
	return (token);
}

static char	**parse_command(char **tokens, t_cmd *current_cmd)
{
	unsigned int	j;
	char			**tmp;

	j = 0;
	while (*tokens && **tokens != '|' && **tokens != ';')
	{
		tmp = parse_token(tokens, current_cmd, &j);
		if (!tmp)
			return (NULL);
		tokens = tmp + 1;
	}
	if (*tokens && **tokens == '|')
		current_cmd->pipe = true;
	free(*tokens);
	*tokens++ = NULL;
	return (tokens);
}

int		replace_env_tokens(char **tokens)
{
	char	**begin;
	char	*env;
	char	*ptr;
	char	*to_replace;

	begin = tokens;
	while (*tokens)
	{
		if (**tokens != '\'')
		{
			ptr = ft_strchr(*tokens, '$');
			while (ptr)
			{
				to_replace = ft_strndup(ptr, ft_wrdlen(ptr));
				if (!to_replace)
					return ((int)parser_failure(begin) - 1);
				env = ft_getenv(to_replace + 1);
				if (!env)
					env = "";
				if (ft_strreplace_first(tokens, to_replace, env, free))
				{
					free(to_replace);
					return ((int)parser_failure(begin) - 1);
				}
				ptr = ft_strchr(ptr + 1, '$');
			}
		}
		tokens++;
	}
	return (0);
}

t_cmd	**parser(char **tokens)
{
	const size_t	count = cmd_count(tokens);
	int				ac;
	t_cmd			**cmd_arr;
	char			**tmp;
	size_t			i;

	if (replace_env_tokens(tokens)
				|| gb_alloc((void **)&cmd_arr, sizeof(t_cmd *) * (count + 1)))
		return (NULL);
	cmd_arr[count] = NULL;
	i = ((size_t)-1);
	while (++i < count)
	{
		ac = arg_count(tokens);
		if (gb_alloc((void **)&cmd_arr[i], sizeof(t_cmd) + ac * sizeof(char *))
					|| lst_init(&cmd_arr[i]->out))
			return (NULL);
		gb_add(cmd_arr[i]->out, lst_destroy_raw);
		cmd_arr[i]->in = NULL;
		cmd_arr[i]->argc = ac;
		tmp = parse_command(tokens, cmd_arr[i]);
		if (!tmp)
			return (parser_failure(tokens));
		tokens = tmp;
	}
	return (cmd_arr);
}
