#include <minishell.h>

static int	check_first_character(char *str)
{
	size_t	i;

	i = 0;
	ft_skip_whitespace(str);
	if (str[i] == ';' || str[i] == '|')
		return (syntax_error(str[i]));
	return (0);
}

static int	check_last_character(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (i > 0 && ft_isspace(str[i]))
		i--;
	if (ft_strchr("<>|", str[i]))
		return (syntax_error(str[i]));
	return (0);
}

static int	check_operator_excess(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("<>|;", str[i]))
		{
			if (str[i] == '>' && str[i + 1] == '>')
				i++;
			i++;
			i += ft_skip_whitespace(str + i);
			if (str[i] == 0)
				return (0);
			else if (ft_strchr("<>|;", str[i]))
				return (syntax_error(str[i]));
		}
		i++;
	}
	return (0);
}

static int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
		{
			i++;
			while (str[i] && str[i] != '"' && str[i - 1] != '\\')
				i++;
			if (str[i] != '"' )
				return (syntax_error(str[i]));
		}
		else if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
		{
			i++;
			while (str[i] && str[i] != '\'' && str[i - 1] != '\\')
				i++;
			if (str[i] != '\'')
				return (syntax_error(str[i]));
		}
		i++;
	}
	return (0);
}

int	check_syntax(char *str)
{
	if (check_first_character(str) || check_last_character(str)
		|| check_operator_excess(str) || check_quotes(str))
		return (1);
	return (0);
}
