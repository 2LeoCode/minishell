#include <minishell.h>

int		ft_addenv(const char *name, const char *value)
{
	struct s_env	*new_env;
	int				i;

	new_env = malloc(sizeof(struct s_env) + env->count + 1);
	if (!new_env)
		return (-1);
	new_env->count = env->count + 1;
	i = -1;
	while (++i < env->count)
		new_env->data[i] = env->data[i];
	new_env->data[env->count] = ft_strcjoin(name, value, '=');
	if (!new_env->data[env->count])
	{
		free(new_env);
		new_env = NULL;
		return (-1);
	}
	free(env);
	env = new_env;
	return (0);
}

int	ft_delenv(const char *name)
{
	struct s_env	*new_env;
	size_t			name_len;
	int				i;
	int				j;

	new_env = malloc(sizeof(struct s_env) + env->count - 1);
	if (!new_env)
		return (-1);
	name_len = ft_strlen(name);
	new_env->count = env->count - 1;
	i = -1;
	j = 0;
	while (++i < env->count)
	{
		if (!ft_memcmp(env->data[i], name, name_len))
			free(env->data[i]);
		else
			new_env->data[j++] = env->data[i];
	}
	free(env);
	env = new_env;
	return (0);
}

char	*ft_getenv(const char *name)
{
	int		i;
	int		j;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (i < env->count && ft_memcmp(env->data[i], name, name_len))
		i++;
	if (!env->data[i])
		return (NULL);
	j = 0;
	while (env->data[i][j] && env->data[i][j] != '=')
		j++;
	return (env->data[i] + j);
}

int	ft_setenv(const char *name, const char *value)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (i < env->count && ft_memcmp(env->data[i], name, name_len))
		i++;
	if (env->data[i])
		ft_delenv(name);
	if (ft_addenv(name, value))
		return (-1);
	return (0);
}

void	ft_clearenv(void)
{
	int	i;

	if (!env)
		return ;
	i = -1;
	while (++i < env->count)
		free(env->data[i]);
	free(env);
	env = NULL;
}
