#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>
#include "libft.h"
#include "list.h"

int	syntax_error(char unexpected_token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putchar_fd(unexpected_token, 2);
	ft_putendl_fd("'", 2);
	return (-1);
}

//r = (rand() % (max + 1 - min)) + min
size_t	ft_skip_whitespace(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

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

char	*tokens[20] = {
	"echo",
	"ls",
	"env",
	"export",
	"cd",
	"pwd",
	" ",
	"|",
	";",
	"<",
	">",
	">>",
	"foo",
	"bar",
	"baz",
	"qux",
	"quux",
	"corge",
	"grault",
	"garply"
};

bool	is_already_done(const t_list *already, const char *cmd) {
	for (const t_list *it = already->next; it != already; it = it->next)
		if (!ft_strcmp(it->data, cmd))
			return (true);
	return (false);
}

int main(void) {
	int fd = open("cmd_file", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	t_list	*already = lst_new();

	srandom(time(NULL));
	for (unsigned token_cnt = 3; token_cnt <= 10; token_cnt++) {
		unsigned	cmd_cnt = 0;
		char		*input_str = NULL;

		while (cmd_cnt < 200) {
			for (unsigned i = 0; i < token_cnt; i++) {
				int		r = random() % 20;
				char	*tmp = input_str ? ft_strcjoin(input_str, tokens[r], ' ') : ft_strdup(tokens[r]);

				free(input_str);
				input_str = tmp;
			}
			if (!is_already_done(already, input_str) && !check_syntax(input_str)) {
				lst_push_back(already, input_str, ft_strlen(input_str) + 1);
				ft_putendl_fd(input_str, fd);
				cmd_cnt++;
			}
			free(input_str);
			input_str = NULL;
		}
		lst_clear(already);
	}
	lst_destroy(already);
	close(fd);
	return (0);
}
