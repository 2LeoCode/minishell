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
**	The parse-and-execute part: we send an input to this function through a
**	string, then we add this input to the command history, then we parse and
**	execute the command.
**
**	for (int i = 0; cmd_array[i]; i++)
**	{
**		printf("---> Command %d <---\n\n", i);
**		printf(	"pipe: %d\n"
**				"r_in: %d\n"
**				"r_out: %d\n"
**				"r_out2: %d\n"
**				"in: %s\n"
**				"out:",
**				cmd_array[i]->pipe,
**				cmd_array[i]->redirect_in,
**				cmd_array[i]->redirect_out,
**				cmd_array[i]->redirect_out2,
**				cmd_array[i]->in);
**		for (t_list *it = cmd_array[i]->out->next; it != cmd_array[i]->out;
**			it = it->next)
**			printf(" %s", it->data);
**		printf(	"\nargc: %d\n"
**				"argv:",
**				cmd_array[i]->argc);
**		for (int j = 0; j < cmd_array[i]->argc; j++)
**			printf(" %s", cmd_array[i]->argv[j]);
**		printf("\n\n");
**	}								Display all command informations
*/

static int	ft_execute(t_shell *ms, t_cmd **cmd_arr)
{
	const int	ret = executer(ms, cmd_arr);

	pre_exit_clear();
	if (g_global_data.sigint)
		g_global_data.sigint = false;
	set_terminal_attributes();
	return (ret);
}

static void	check_runtime_error(void)
{
	if (errno == ENOMEM)
	{
		minishell_error();
		minishell_exit(-1);
	}
	g_global_data.status = 258;
}

static int	process_input(t_shell *ms, char *input)
{
	t_cmd	**cmd_array;
	char	**tokens;
	size_t	token_cnt;
	int		ret;

	(void)ms;
	ret = 0;
	if (*input && push_history(input))
		return (-1);
	cmd_array = NULL;
	tokens = lexer(input, &token_cnt);
	free(input);
	if (tokens)
		cmd_array = parser(tokens, token_cnt);
	pre_exit_save(cmd_array, tokens, token_cnt);
	if (!tokens || !cmd_array)
		check_runtime_error();
	else
	{
		reset_terminal_attributes();
		ret = ft_execute(ms, cmd_array);
	}
	return (ret);
}

static void	prompt(t_shell *ms, char **input_ptr)
{
	int	read_ret;
	int	cmd_ret;

	read_ret = 1;
	while (42)
	{
		write(1, "minishell-1.0$ ", 15);
		read_ret = get_input(ms, input_ptr);
		if (read_ret == 2)
			break ;
		if (read_ret != -1)
			cmd_ret = process_input(ms, *input_ptr);
		if (read_ret == -1 || cmd_ret == -1)
		{
			perror("minishell");
			minishell_exit(-1);
		}
	}
	free(*input_ptr);
	ft_putendl("exit");
	save_history();
	tcsetattr(0, 0, &g_global_data.term_backup);
	minishell_clear();
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	ms;

	(void)argc;
	minishell_init(&ms, argv[0]);
	if ((setup_signal() == SIG_ERR)
		|| minishell_setup(&ms, envp))
		return (minishell_error());
	prompt(&ms, &input);
	return (0);
}
