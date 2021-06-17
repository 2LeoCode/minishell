/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:35:54 by lsuardi           #+#    #+#             */
/*   Updated: 2021/04/03 15:02:17 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	no_such_file(const char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	perror(path);
	return (1);
}

int	handle_tilde(char *arg, char *home)
{
	char	*path;
	int		ret;

	path = arg;
	if (!home)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	if (ft_strreplace_first(&path, "~", home, NULL))
		return (-1);
	ret = chdir(path);
	if (ft_setenv("PWD", path))
		return (-1);
	free(path);
	if (ret)
		return (no_such_file(arg));
	return (0);
}

int	handle_argv(char ac, char *home, char *arg)
{
	int	ret;

	if (ac == 1)
	{
		if (chdir(home))
			return (no_such_file(arg));
	}
	else if (arg[0] == '~')
	{
		ret = handle_tilde(arg, home);
		if (ret)
			return (ret);
	}
	else if (!ft_strcmp(arg, "-"))
	{
		if (chdir(ft_getenv("OLDPWD")))
			return (no_such_file(arg));
	}
	else if (chdir(arg))
		return (no_such_file(arg));
	return (0);
}

int	builtin_cd(int argc, char **argv, char **envp)
{
	char	*home;
	char	*new_pwd;
	int		ret;

	(void)envp;
	home = ft_getenv("HOME");
	ret = handle_argv(argc, home, argv[1]);
	if (ret)
		return (ret);
	if (ft_setenv("OLDPWD", ft_getenv("PWD")))
		return (-1);
	new_pwd = ft_get_current_dir_name();
	if (!new_pwd)
		return (-1);
	ret = ft_setenv("PWD", new_pwd);
	free(new_pwd);
	if (ret)
		return (-1);
	return (0);
}
