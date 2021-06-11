%:include <stdio.h>
%:include <limits.h>

%:define concat(h, e, l, _l, o, _, w, _o, r, _l_, d) _ ## h ## r ## l
%:define magic concat(a, b, n, o, r, m, _a, l, i, t, y)
%:define magical_trick concat(e, w, t, f, p, _t, l, o, x, q, k)

typedef unsigned long	size_t;

int	magic(void) <%
	char _text<:14:> = "Hello World !";

	printf("%s\n", magical_trick);
	return (0);
%>
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
		if (**tokens ==  '|' || (**tokens == ';' && tokens[1]))
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

t_cmd	**parser(char **tokens)
{
	const size_t	count = cmd_count(tokens);
	int				ac;
	t_cmd			**cmd_arr;
	char			**tmp;
	size_t			i;

	if (gb_alloc((void **)&cmd_arr, sizeof(t_cmd *) * (count + 1)))
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
		printf("[   %zu   ]\n", i);
		tmp = parse_command(tokens, cmd_arr[i]);
		if (!tmp)
		{
			ft_destroy_array((void **)tokens, count);
			return (NULL);
		}
		tokens = tmp;
	}
	return (cmd_arr);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:38:22 by lsuardi           #+#    #+#             */
/*   Updated: 2021/04/03 18:22:37 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
**	In that function we have our data structures and the last key that has been
**	pressed. So we will check for every "action" keys (ENTER, arrow keys, and
**	DEL key), or if the key is a printable character that we can display, and
**	then we call different function and return different values:
**	If the key value is -1, it will mean that an error occurred in our
**	`ft_getchar` function (so `read` returned -1), or if an allocation failed,
**	we will return -1, else we will return 1 only if `key` is ENTER to inform
**	that the command has been sent to the program, otherwise we will return 0.
*/
static int		process_key(t_shell *ms, t_input *input, int key)
{
	int ret;

	if (g_global_data.sigint)
	{
		g_global_data.sigint = false;
		reset_input(input, NULL);
	}
	if (key == -1)
		return (-1);
	if (key == _KEY_ENTER)
		return (1);
	if (ft_isprint(key) && process_key_print(input, key))
		return (-1);
	else if (key == _KEY_DELETE)
	{
		if (!input->index)
			return (0);
		if (process_key_del(input))
			return (-1);
	}
	else if (key == _KEY_LEFT)
		return (process_key_left(&ms->tcaps, input));
	else if (key == _KEY_RIGHT)
		return (process_key_right(&ms->tcaps, input));
	else if (((key == _KEY_UP) || (key == _KEY_DOWN))
	&& !!(ret = process_key_hist(g_global_data.history, input, key)))
		return (-1 * (ret == -1));
	return (update_input(&ms->tcaps, input));
}

/*
**	The function to handle input in non-canonical mode (to be able to move the
**	cursor and to have a command history):
**	We have our input struct that we setup with default values (the cursor index
**	is 0 at the beginning as well as the history pointer initially points to the
**	last command in history), we then call our `process_key` function (see
**	above), we send it our main struct ms, the address of our input struct to be
**	able to edit it, and the key which is pressed through a custom `ft_getchar`
**	function that handles non ascii keys that wee need such as ENTER, LEFT, ...
**	(see libft for `ft_getchar`). `process_key` will return 1 when the ENTER key
**	is pressed, otherwise it will return 0, so we loop on that function until it
**	returns a non null value to process every key one by one.
**	Then we check if the return value is -1, which means that an error occured,
**	in that case we will just free the input string (`input.in`), else we write
**	a new line and we put the input in `*final_input` string.
**	We then return `ret` which is the last return value of `process_key` (-1 on
**	failure or 1 on success)
*/
static int		get_input(t_shell *ms, char **final_input)
{
	t_input		input;
	int			ret;

	if (!(input.in = ft_strdup("")))
		return (-1);
	input.index = 0;
	input.prev_index = 0;
	input.hist = g_global_data.history;
	input.prev_len = 0;
	while (!(ret = process_key(ms, &input, ft_getchar())))
		continue ;
	if (ret == -1)
		free(input.in);
	else
	{
		write(1, "\n", 1);
		*final_input = input.in;
	}
	return (ret);
}

/*
**	The parse-and-execute part: we send an input to this function through a
**	string, then we add this input to the command history, then we parse and
**	execute the command.
*/
static int		process_input(t_shell *ms, char *input)
{
	t_cmd	**cmd_array;
	char	**tokens;

	(void)ms;
	if (*input && ((!lst_size(g_global_data.history)
				|| ft_strcmp(input, (char*)g_global_data.history->next->data))
				&& lst_push_front(g_global_data.history, input, ft_strlen(input) + 1)))
		return (-1);
	gb_save();
	cmd_array = NULL;
	tokens = lexer(input);
	if (tokens)
		cmd_array = parser(tokens);
	if (!tokens || !cmd_array)
	{
		perror("minishell");
		minishell_exit(-1);
	}
	return (0);
}

static void		prompt(t_shell *ms, char **input_ptr)
{
	int		read_ret;

	read_ret = 1;
	while (1)
	{
		write(1, "minishell-1.0$ ", 15);
		if (((read_ret = get_input(ms, input_ptr)) == -1)
					|| (read_ret && ((process_input(ms, *input_ptr) == -1))))
		{
			perror("minishell");
			minishell_exit(-1);
		}
	}
}

int 			main(int argc, char **argv, char **envp)
{
	char		*input;
	t_shell		ms;

	(void)argc;
	if (gb_add(&ms, minishell_clear))
		return (-1);
	minishell_init(&ms, argv[0]);
	if ((setup_signal() == SIG_ERR)
	|| minishell_setup(&ms, envp))
		return (minishell_error());
	prompt(&ms, &input);
	return (0);
}
