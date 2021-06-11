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

	i = 0;
	arr = ft_calloc(size + 1, sizeof(char*));
	if (!arr)
		return NULL;
	while (i++ < size)
	{
		arr[i] = ft_strdup(src[i]);
		if (!arr[i])
			ft_destroy_array((void **)arr, NULL_ENDED);
	}
	return (arr);
}

int		retrieve_env(char **backup)
{
	size_t i;

	i = 0;
	while (backup[i])
		i++;
	g_global_data.env = malloc(sizeof(struct s_env) + (i + 1) * sizeof(char *));
	if (!g_global_data.env)
		return (-1);
	g_global_data.env->count = i;
	i = 0;
	while (backup[i])
		g_global_data.env->data[i] = backup[i++];
	g_global_data.env->data[i] = NULL;
	free(backup);
	return (0);
}

int		env_failure(char **backup, char **path, int ret)
{
	ft_destroy_array(path, NULL_ENDED);
	ft_clearenv();
	if (retrieve_env(backup) == -1)
		env_failure(backup, NULL, -1);
	printf("syntax error");
	return (ret);
}

void	print_env(char **ep)
{
	while (*ep && strchr(**ep, '='))
	{
		printf("%s\n", *ep);
		ep++;
	}
}

int		minishell_exec(char **av, char **ep)
{

}

int		handle_cmdargs(char ***av)
{
	char *rpl;

	while (**av)
	{
		rpl = ft_rplchr(**av, '=', '\0');
		if (!rpl)
			break ;
		if (!***av)
			return (1);
		if (ft_setenv(**av, rpl + 1) == -1)	// Attention !! Changer retour de ft_rplchr() pour qu'il return le pointeur sur caractere remplace. && Faire en sorte que set_env() mette une string vide si *rpl == "\0".
			return (-1);
		(*av)++;
	}
	return (0);
}

int		handle_env_outcome(char **av, char **ep, char **backup, char **path)
{
	char	*full_path;

	full_path = get_first_path(*av, path);
	if (errno == ENOMEM)
		return (env_failure(backup, path, 127));
	if (*av && full_path)
        minishell_exec(full_path, ep);
    else
	{
		if (!*av)							// dans le cas ou on rentre ici, c'est soit qu'on arrive a la fin de av et on print, soit ce n'est pas une commande et donc erreur.
        	print_env(ep);
		else
		{
			free(full_path);
			return (env_failure(backup, path, 127));
		}
	}
	free(full_path);
}

int		builtin_env(int ac, char **av, char **ep)
{
	char	**path;
	char	**backup;
	int		i;
	int		ret;

	(void)ac;
	i = 0;
	path = ft_split(ft_getenv("PATH"), ':');
	if (!path)
		return (-1);
    backup = strarr_dup(ep, g_global_data.env->count);			// Creer une fonction dans la lib qui fait une copie d'un tableau de string vers un a
	if (!backup)
	{
		ft_destroy_array(path, NULL_ENDED);
		return (-1);
	}
	av++;
	ret = handle_cmdargs(&av);
	if (ret != 0)
		return (env_failure(backup, path, ret));
	ft_destroy_array(path, NULL_ENDED);
	ft_clearenv();
	if (retrieve_env(backup) == -1)
		env_failure(backup, NULL, -1);
	return (0);
}
