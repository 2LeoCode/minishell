#include <minishell.h>

size_t	ft_skip_whitespace(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

size_t	skip_quote_token(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] && i != 0 && str[i - 1] != '\\')
		return (1);
	if (str[i] == '"')
	{
		i++;
		while (str[i] && (str[i] != '"'))
			i++;
		if (str[i] == '"')
			i++;
	}
	else if (str[i] == '\'')
	{
		i++;
		while (str[i] && (str[i] != '\''))
			i++;
		if (str[i] == '\'')
			i++;
	}
	return (i);
}

size_t	get_next_token(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '<' || str[i] == '>')
	{
		i++;
		if (str[i] == '>')
			i++;
	}
	else if (str[i] == '|' || str[i] == ';')
		i++;
	else
	{
		while (str[i] && !ft_strchr(" |<>;", str[i]))
		{
			if (str[i] == '\'' || str[i] == '\"')
				i += skip_quote_token(&str[i]);
			else
				i++;
		}
	}
	i += ft_skip_whitespace(str + i);
	return (i);
}
