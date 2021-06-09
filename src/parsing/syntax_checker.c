//#include "minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int		ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\r' || c == '\n' || c == '\v' || c == '\t');
}

size_t  ft_skip_whitespace(char *str)
{
	size_t  i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

int     check_first_character(char *str)
{
	size_t  i;  

	i = 0;
	ft_skip_whitespace(str);
	if (str[i] == ';' || str[i] == '|')
		return (1);
	return (0);
}

int     check_last_character(char *str)
{
	size_t  i;  

	i = 0;
	while (str[i])
		i++;
	i--;
	while (i > 0 && ft_isspace(str[i]))
		i--;
	//	printf("%zu %c\n", i, str[i]);
	if (str[i] == '|')
		return (2);
	return (0);
}

int     check_operator_excess(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (strchr("<>|;", str[i]))
		{
			printf("i = %i\n", i);
			if (str[i] == '>' && str[i + 1] == '>')
				i++;
			i++;
			i += ft_skip_whitespace(str + i);
			printf("i = %i\n", i);
			printf("str[i] = %c\n", str[i]);
			if (strchr("<>|;", str[i]))
			{
				write(1, "kek\n", 4);
				return (3);
			}
		}
		i++;
	}   
	return (0);
}

/*
   int     check_double_cmdseparator(char *str)
   {
   size_t  i;

   i = 0;
   while (str[i])
   {
   if (str[i] == '|')
   {
   i += ft_skip_whitespace(str);
   if (str[i] == '|')
   return (3);
   }
   if (str[i] == ';')
   {
   i += ft_skip_whitespace(str);
   if (str[i] == ';')
   return (3);
   }
   }
   return (0);
   }
*/

int main(int argc, char **argv)
{
	//	char *str = "echo bonjour | cat -e ;   \t\v|   \n  ";

	(void)argc;
	printf("check_last_character = %i\n", check_last_character(argv[1]));
	printf("check_first_character = %i\n", check_first_character(argv[1]));
	printf("check_operator_excess = %i\n", check_operator_excess(argv[1]));
	return (0);
}
