/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 23:55:08 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/28 23:55:19 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**strarr_dup(char **src, size_t size)
{
	char	**arr;
	size_t		i;

	i = -1;
	arr = ft_calloc(size + 1, sizeof(char *));
	if (!arr)
		return NULL;
	while (++i < size)
	{
		arr[i] = ft_strdup(src[i]);
		if (!arr[i])
		{
			ft_destroy_array((void **)arr, NULL_ENDED);
			return (NULL);
		}
	}
	return (arr);
}

int		retrieve_env(char **backup, char *path_backup)
{
	size_t i;

	i = 0;
	while (backup[i])
		i++;
	g_global_data.env = malloc(sizeof(struct s_env) + (i + 1) * sizeof(char *));
	if (!g_global_data.env)
		return (-1);
	g_global_data.env->count = i;
	i = -1;
	while (backup[++i])
		g_global_data.env->data[i] = backup[i];
	g_global_data.env->data[i] = NULL;
	free(backup);
	if (path_backup && update_path(path_backup))
		return (-1);
	free(path_backup);
	return (0);
}

int		env_failure(char **backup, int ret)
{
	ft_destroy_array((void **)backup, NULL_ENDED);
	return (ret);
}

void	print_env(char **ep)
{
	while (*ep && ft_strchr(*ep, '='))
	{
		ft_putendl(*ep);
		ep++;
	}
}

void		minishell_exec(char *path, char **av, char **ep)
{
	pid_t pid;

	(void)av;
	(void)ep;
	pid = fork();
	if (pid == -1)
		perror("minishell");
	if (pid == 0)
	{
		execve(path, av, ep);
		perror("minishell");
	}
	waitpid(pid, &g_global_data.status, 0);
}

int		handle_cmdargs(char ***av, char **path_backup)
{
	char *rpl;

	while (**av)
	{
		rpl = ft_rplchr(**av, '=', '\0');
		if (!rpl)
			break ;
		if (!***av)
			return (1);
		if (!ft_strcmp(**av, "PATH"))
		{
			*path_backup = ft_getenv("PATH");
			if (*path_backup)
			{
				*path_backup = ft_strdup("PATH");
				if (!*path_backup)
					return (-1);
			}
			if (update_path(rpl + 1))
			{
				free(*path_backup);
				return (-1);
			}
		}
		else if (ft_setenv(**av, rpl + 1) == -1)	// Attention !! Changer retour de ft_rplchr() pour qu'il return le pointeur sur caractere remplace. && Faire en sorte que set_env() mette une string vide si *rpl == "\0".
			return (-1);
		(*av)++;
	}
	return (0);
}

int		handle_env_outcome(char **av, char **ep)
{
	char	*full_path;

	full_path = NULL;
	if (*av)
		full_path = get_first_path(*av);
	if (errno == ENOMEM)
		return (127);
	if (*av && full_path)
        minishell_exec(full_path, av, ep);
    else if (!*av)						// dans le cas ou on rentre ici, c'est soit qu'on arrive a la fin de av et on print, soit ce n'est pas une commande et donc erreur.
    	print_env(ep);
    else
	{
    	free(full_path);
    	return (127);
	}
	free(full_path);
    return (0);
}

int		builtin_env(int ac, char **av, char **ep)
{
	char	**backup;
	char	*path_backup;
	int		ret;

	(void)ac;
	path_backup = NULL;
    backup = strarr_dup(ep, g_global_data.env->count);			// Creer une fonction dans la lib qui fait une copie d'un tableau de string vers un a
	if (!backup)
		return (-1);
	av++;
	ret = handle_cmdargs(&av, &path_backup);
	if (ret != 0)
		return (env_failure(backup, ret));
	ret = handle_env_outcome(av, ep);
	if (ret != 0)
		return (env_failure(backup, ret));
	if (ret == -1)
		return (-1);
	ft_clearenv();
	if (retrieve_env(backup, path_backup) == -1)
		return (-1);
	return (0);
}
