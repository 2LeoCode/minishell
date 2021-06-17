#include <minishell.h>

static int	replace_questionmark_env(char *token)
{
	char	*env;

	env = ft_itoa(g_global_data.status);
	if (!env || ft_strreplace_first(&token, "$?", env, free))
	{
		free(env);
		return (-1);
	}
	free(env);
	return (0);
}

static int	replace_regular_env(char *token, char *ptr_to_dollar)
{
	char	*to_replace;
	char	*env;
	bool	failure;

	failure = false;
	to_replace = ft_strndup(ptr_to_dollar, ft_wrdlen(ptr_to_dollar));
	ft_rplchr(to_replace, '\"', 0);
	if (!to_replace)
		return (-1);
	env = ft_getenv(to_replace + 1);
	if (!env)
		env = "";
	if (ft_strreplace_first(&token, to_replace, env, free))
		failure = true;
	free(to_replace);
	if (failure)
		return (-1);
	return (0);
}

int	replace_env_tokens(char **tokens)
{
	char	*ptr;

	while (*tokens)
	{
		if (**tokens != '\'')
		{
			ptr = ft_strchr(*tokens, '$');
			while (ptr)
			{
				if (!ft_memcmp(ptr, "$?", 2))
				{
					if (replace_questionmark_env(*tokens))
						return (-1);
				}
				else if (replace_regular_env(*tokens, ptr))
					return (-1);
				ptr = ft_strchr(ptr + 1, '$');
			}
		}
		tokens++;
	}
	return (0);
}
