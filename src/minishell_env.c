#include <minishell.h>

void	ft_printenv(void)
{
	for (int i = 0; i < g_global_data.env->count; i++)
		printf("%d: %s\n", i, g_global_data.env->data[i]);
}

int		ft_addenv(const char *name, const char *value)
{
	struct s_env	*new_env;
	int				i;

	new_env = malloc(sizeof(struct s_env)
		+ (g_global_data.env->count + 1) * sizeof(char *));
	if (!new_env)
		return (-1);
	new_env->count = g_global_data.env->count + 1;
	i = -1;
	while (++i < g_global_data.env->count)
		new_env->data[i] = g_global_data.env->data[i];
	new_env->data[i] = ft_strcjoin(name, value, '=');
	if (!new_env->data[i])
	{
		free(new_env);
		new_env = NULL;
		return (-1);
	}
	free(g_global_data.env);
	g_global_data.env = new_env;
	return (0);
}

int	ft_delenv(const char *name)
{
	struct s_env	*new_env;
	size_t			name_len;
	int				i;
	int				j;

	new_env = malloc(sizeof(struct s_env)
		+ (g_global_data.env->count - 1) * sizeof(char *));
	if (!new_env)
		return (-1);
	name_len = ft_strlen(name);
	new_env->count = g_global_data.env->count - 1;
	i = -1;
	j = 0;
	while (++i < g_global_data.env->count)
	{
		if (!ft_memcmp(g_global_data.env->data[i], name, name_len))
			free(g_global_data.env->data[i]);
		else
			new_env->data[j++] = g_global_data.env->data[i];
	}
	free(g_global_data.env);
	g_global_data.env = new_env;
	return (0);
}

char	*ft_getenv(const char *name)
{
	const size_t	name_len = ft_strlen(name);
	int				i;
	size_t			current_env_len;

	i = 0;
	while (i < g_global_data.env->count)
	{
				
		current_env_len = ft_strlen(g_global_data.env->data[i]);
		if (current_env_len > name_len
				&& (g_global_data.env->data[i][name_len] != '='
				|| ft_memcmp(g_global_data.env->data[i], name, name_len)))
			break ;
		i++;
	}
	if (!g_global_data.env->data[i])
		return (NULL);
	return (g_global_data.env->data[i] + name_len + 1);
}

int	ft_setenv(const char *name, const char *value)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (i < g_global_data.env->count
				&& (g_global_data.env->data[i][name_len] == '='
				|| ft_memcmp(g_global_data.env->data[i], name, name_len)))
		i++;
	if (g_global_data.env->data[i])
		ft_delenv(name);
	if (ft_addenv(name, value))
		return (-1);
	return (0);
}

void	ft_clearenv(void)
{
	int	i;

	if (!g_global_data.env)
		return ;
	i = -1;
	while (++i < g_global_data.env->count)
		free(g_global_data.env->data[i]);
	free(g_global_data.env);
	g_global_data.env = NULL;
}
