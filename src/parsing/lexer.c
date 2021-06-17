/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:32:29 by mhenry            #+#    #+#             */
/*   Updated: 2021/06/05 12:08:16 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

size_t	token_cnt(char *str)
{
	char	*sentinel;
	size_t	i;
	size_t	cnt;

	cnt = 0;
	i = ft_skip_whitespace(str);
	sentinel = str + i;
	while (str[i])
	{
		cnt++;
		i += get_next_token(sentinel);
		sentinel = str + i;
	}
	return (cnt);
}

char	*token_alloc(char *str)
{
	char	*token;
	size_t	i;

	i = 0;
	while (str[i] && !ft_strchr(" |<>;", str[i]))
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += skip_quote_token(&str[i]);
		else
			i++;
	}
	if (str[0] == '>' && str[1] == '>')
		token = ft_strdup(">>");
	else if (ft_strchr("|<>;", str[0]))
		token = ft_strndup(str, 1);
	else
		token = ft_strndup(str, i);
	return (token);
}

char	**tkntab_alloc(char *str, size_t cnt)
{
	char	**arr;
	size_t	i;
	size_t	j;

	arr = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!arr)
		return (NULL);
	i = ft_skip_whitespace(str);
	j = 0;
	while (str[i])
	{
		arr[j] = token_alloc(str + i);
		if (!arr[j])
		{
			ft_destroy_array((void **)arr, NULL_ENDED);
			return (NULL);
		}
		i += get_next_token(str + i);
		j++;
	}
	arr[j] = NULL;
	return (arr);
}

char	**lexer(char *input_str, size_t *token_count)
{
	if (ft_strisspace(input_str) || check_syntax(input_str))
		return (NULL);
	*token_count = token_cnt(input_str);
	return (tkntab_alloc(input_str, *token_count));
}

/*
int main(int argc, char **argv)
{
	char	**cmd_tab;
	size_t	i;

	i = 1;
	if (argc < 2)
		return (1);
	printf("token_count = %zu\n", token_cnt(argv[1]));
	cmd_tab = lexer(argv[1]);
	i = 0;
	while (i < token_cnt(argv[1]))
	{
		printf("%s\n", cmd_tab[i]);
		i++;
	}
	return (0);
}
*/

/*int main(void)
{
	int n;
	char *str = "bonjour |     ";

	n = check_last_character(str);
	printf("%i\n", n);
}
*/
