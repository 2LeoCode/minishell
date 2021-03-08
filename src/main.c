/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:38:22 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/04 20:11:07 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int execute_cmd(char * input)
{
	char *	cmd;
	char **	argv;

	while (*input)
	{
		if (!(cmd = get_cmd(&input)))
			return (-1);
	}
	return (0);
}

int main(int argc, char ** argv, char ** envp)
{
	char *		input;
	int			read_ret;
	t_shell		ms;

	(void)argc;
	minishell_init(&ms, argv[0]);
	if ((signal(SIGINT, &int_handler) == SIG_ERR)
	|| minishell_setup(&ms, envp))
		return (minishell_error());
	read_ret = 1;
	while (read_ret > 0)
	{
		write(1, "minishell-1.0# ", 15);
		if ((read_ret = get_next_line(0, &input)) == -1
		|| (read_ret && (execute_cmd(input) == -1)))
			return (minishell_error());
		free(input);
	}
	return (0);
}
