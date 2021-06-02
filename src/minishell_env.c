#include <minishell.h>

int		ft_addenv(const char *name, const char *value)
{
	char	**new_env;
	int		i;

	env->count++;
	new_env = (char **)malloc(sizeof(char *) * env->count + 1);
	if (!new_env)
		return (-1);

}

const char	*ft_getenv(const char *name)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (i < env.count && ft_strncmp(env.data[i], name, name_len))
		i++;
	if (env[i])
		return (env[i]);
	return (NULL);
}

int	ft_setenv(const char *name, const char *value)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (env[i] && ft_strncmp(env[i], name, name_len))
		i++;
	if (env[i])
		ft_delenv(name);
	if (ft_addenv(name, value))
		return (-1);
	return (0);
}
