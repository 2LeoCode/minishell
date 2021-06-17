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
		free(*token);
		current_cmd->in = *++token;
		*token = NULL;
		if (!is_valid_file(current_cmd->in))
			return (NULL);
	}
	else
	{
		current_cmd->argv[(*index)++] = *token;
		*token = NULL;
	}
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

static int	cmd_init(t_cmd **cmd_ptr, int ac)
{
	*cmd_ptr = malloc(sizeof(t_cmd) + (ac + 1) * sizeof(char *));
	(*cmd_ptr)->redirect_out = false;
	(*cmd_ptr)->redirect_out2 = false;
	(*cmd_ptr)->pipe = false;
	(*cmd_ptr)->argv[ac] = NULL;
	(*cmd_ptr)->in = NULL;
	(*cmd_ptr)->argc = ac;
	if (!*cmd_ptr || lst_init(&(*cmd_ptr)->out))
		return (-1);
	return (0);
}

static int	create_new_cmd(char ***token_ptr, t_cmd **cmd_ptr)
{
	int		ac;
	char	**tmp;

	ac = arg_count(*token_ptr);
	if (cmd_init(cmd_ptr, ac))
		return (-1);
	tmp = parse_command(*token_ptr, *cmd_ptr);
	if (!tmp)
		return (-1);
	*token_ptr = tmp;
}

t_cmd	**parser(char **tokens, size_t token_cnt)
{
	const size_t	count = cmd_count(tokens);
	char			**begin_tokens;
	t_cmd			**cmd_arr;
	size_t			i;

	begin_tokens = tokens;
	cmd_arr = ft_calloc(count + 1, sizeof(t_cmd *));
	if (!cmd_arr || replace_env_tokens(tokens))
		return (NULL);
	cmd_arr[count] = NULL;
	i = -1;
	while (++i < count)
		if (create_new_cmd(&tokens, &cmd_arr[i]))
			return (parser_failure(begin_tokens, token_cnt, cmd_arr));
	return (cmd_arr_without_quotes(cmd_arr));
}
