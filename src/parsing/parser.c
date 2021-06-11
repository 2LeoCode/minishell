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

void	destroy_cmd_array(t_cmd **cmd_arr)
{
	t_cmd	**it;

	it = cmd_arr;
	while (*it)
	{
		lst_destroy((*it)->out);
		free((*it)->in);
		free(*it);
		it++;
	}
	free(cmd_arr);
}

static void		*parser_failure(char **tokens, size_t token_cnt, t_cmd **cmd_arr)
{
	t_cmd	**it;
	
	it = cmd_arr - 1;
	ft_destroy_array((void **)tokens, token_cnt);
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

static bool	is_valid_file(char *path)
{
	int	test_fd;

	test_fd = open(path, O_RDONLY);
	if (test_fd == -1)
		return (false);
	close(test_fd);
	return (true);
}

static char	**parse_token(char **token, t_cmd *current_cmd, unsigned int *index)
{
	if (**token == '>')
	{
		current_cmd->redirect_out = !(*token)[1];
		current_cmd->redirect_out2 = (*token)[1];
		free(*token);
		*token++ = NULL;
		if (!is_valid_file(*token)
					|| lst_push_front(current_cmd->out, *token, ft_strlen(*token) + 1))
			return (NULL);
		free(*token);
		*token = NULL;
	}
	else if (**token == '<')
	{
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
		printf("%s\n", *tokens);
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
	bool	failure;

	begin = tokens;
	failure = false;
	while (*tokens)
	{
		if (**tokens != '\'')
		{
			ptr = ft_strchr(*tokens, '$');
			while (ptr)
			{
				if (!ft_memcmp(ptr, "$?", 2))
				{
					env = ft_itoa(g_global_data.status);
					if (!env || ft_strreplace_first(&ptr, "$?", env, NULL))
					{
						free(env);
						return (-1);
					}
					free(env);
					ptr = ft_strchr(ptr + 1, '$');
					continue ;
				}
				to_replace = ft_strndup(ptr, ft_wrdlen(ptr));
				if (!to_replace)
					return (-1);
				env = ft_getenv(to_replace + 1);
				if (!env)
					env = "";
				if (ft_strreplace_first(tokens, to_replace, env, free))
					failure = true;
				free(to_replace);
				if (failure)
					return (-1);
				ptr = ft_strchr(ptr + 1, '$');
			}
		}
		tokens++;
	}
	return (0);
}

t_cmd	**parser(char **tokens, size_t token_cnt)
{
	const size_t	count = cmd_count(tokens);
	char			**begin_tokens;
	int				ac;
	t_cmd			**cmd_arr;
	char			**tmp;
	size_t			i;

	begin_tokens = tokens;
	cmd_arr = malloc(sizeof(t_cmd *) * (count + 1));
	if (!cmd_arr || replace_env_tokens(tokens))
		return (NULL);
	cmd_arr[count] = NULL;
	i = ((size_t)-1);
	while (++i < count)
	{
		ac = arg_count(tokens);
		cmd_arr[i] = malloc(sizeof(t_cmd) + (ac + 1) * sizeof(char *));
		cmd_arr[i]->argv[ac] = NULL;
		if (!cmd_arr[i] || lst_init(&cmd_arr[i]->out))
			return (parser_failure(begin_tokens, token_cnt, cmd_arr));
		cmd_arr[i]->in = NULL;
		cmd_arr[i]->argc = ac;
		tmp = parse_command(tokens, cmd_arr[i]);
		if (!tmp)
			return (parser_failure(begin_tokens, token_cnt, cmd_arr));
		tokens = tmp;
	}
	return (cmd_arr);
}
