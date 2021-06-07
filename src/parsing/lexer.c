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

//#include "minishell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

size_t	ft_skip_space(char *str)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

int		check_syntax(char *str)
{
	
}

size_t	skip_quote_token(char *str)
{
	size_t i;

	i = 0;
	if (str[i] == '"')
	{
		i++;
		while (str[i] && (str[i] != '"'))
			i++;
		if (str[i] == '"')
			i++;
	}
	else
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
	size_t i;

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

		while (str[i] && !strchr(" |<>;", str[i]))
		{
			if (str[i] == '\'' || str[i] == '\"')
				i += skip_quote_token(&str[i]);
			else
				i++;
		}
	}
	i += ft_skip_space(str + i);
	return (i);
}

size_t	token_cnt(char *str)
{
	char	*sentinel;
	size_t	i;
	size_t	cnt;

	cnt = 0;
	i = ft_skip_space(str);
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
	while (str[i] && !strchr(" |<>;", str[i]))
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += skip_quote_token(&str[i]);
		else
			i++;
	}
	if (strchr("|<>;", str[0]))
	{
		token = strndup(str, 1);
	}
	else
		token = strndup(str, i);
	return (token);
}

char	**tkntab_alloc(char *str, size_t cnt)
{
	char	**tab;
	size_t	i;
	size_t	j;

	tab = malloc(sizeof(char *) * cnt + 1);  // MALLOC !
//	if (tab == NULL)
//		MINISHELL_FAILURE;
	i = ft_skip_space(str);
	j = 0;
	while (str[i])
	{
		tab[j] = token_alloc(str + i);
		i += get_next_token(str + i);
		j++;
	}
	tab[j] = NULL;
	return (tab);
}


char **lexer(char *input_str)
{
	size_t	cnt;

//	if (check_syntax(str))
//		return (NULL);
	cnt = token_cnt(input_str);
	return (tkntab_alloc(input_str, cnt));
}


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
