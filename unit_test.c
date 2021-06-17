//#include <minishell.h>
//#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include "inc/libft.h"

char *path = "/home/user42/Bureau/42-projects/minishell/minishell/";

char *cmds[] = {
	"echo","cd","exit","env","export","unset","pwd","ls",
	NULL
};

char *operators[] = {
	"<",">",">>","|",";",
	NULL
};

char *file_args[] = {
	"file1", "file2", "file3",
	NULL
};

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	char		*tab;

	if (!s1)
		return (NULL);
	if (!(tab = malloc(sizeof(char) * (strlen((char *)s1) +
	strlen((char *)s2)) + 1)))
		return (NULL);
	i = 0;
	while (i < strlen((char *)s1))
	{
		tab[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < strlen((char *)s2))
	{
		tab[i + j] = s2[j];
		j++;
	}
	tab[i + j] = 0;
	return (tab);
}

int	simple_cmd_combos()
{
	char complete_path[68];
	int fd;
	int i;

	bzero(complete_path, 68);
	strcpy(complete_path, path);
	i = 0;
	strcat(complete_path, "simple_cmd_file");
	fd = open(complete_path, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	printf("complete_path = %s\n", complete_path);
	printf("fd = %i\n", fd);
	if (fd < 0)
		return (-1);
	while (cmds[i])
	{
		write(fd, cmds[i], strlen(cmds[i]));
		write(fd, "\n", 1);
		i++;
	}
	i = 0;
	while (operators[i])
	{
		write(fd, operators[i], strlen(operators[i]));
		write(fd, "\n", 1);
		i++;
	}
	i = 0;
	while (file_args[i])
	{
		write(fd, file_args[i], strlen(file_args[i]));
		write(fd, "\n", 1);
		i++;
	}
	close(fd);
	return (0);
}

void	write_double_cmd_combos(int fd, char *str1, char *str2)
{
	write(fd, str1, strlen(str1));
	write(fd, " ", 1);
	write(fd, str2, strlen(str2));
}

int	double_cmd_combos()
{
	char **master[4];
	int fd;
	int i;
	int j;
	int k;
	int l;
	char complete_path[68];

	master[0] = cmds;
	master[1] = operators;
	master[2] = file_args;
	master[3] = NULL;
	bzero(complete_path, 68);
	strcpy(complete_path, path);
	strcat(complete_path, "double_cmd_file");
	fd = open(complete_path, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (fd < 0)
		return (-1);
	k = 0;
	while (master[k])
	{
		l = 0;
		while (master[l])
		{
			i = 0;
			while (master[k][i])
			{
				j = 0;
				while (master[l][j])
				{
					write_double_cmd_combos(fd, master[k][i], master[l][j]);
					write(fd, "\n", 1);
					j++;
				}
				i++;
			}
			l++;
		}
		k++;
	}
	close(fd);
	return (0);
}

void	write_triple_cmd_combos(int fd, char *str1, char *str2, char *str3)
{
		write(fd, str1, strlen(str1));
		write(fd, " ", 1);
		write(fd, str2, strlen(str2));
		write(fd, " ", 1);
		write(fd, str3, strlen(str3));
}

int	triple_cmd_combos()
{
	char **master[4];
	int fd;
	int i;
	int j;
	int k;
	int l;
	int m;
	int n;
	char complete_path[68];

	master[0] = cmds;
	master[1] = operators;
	master[2] = file_args;
	master[3] = NULL;
	bzero(complete_path, 68);
	strcpy(complete_path, path);
	strcat(complete_path, "triple_cmd_file");
	fd = open(complete_path, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	fd = open("triple_cmd_file", O_RDWR);
	if (fd < 0)
		return (-1);
	l = 0;
	while (master[l])
	{
		m = 0;
		while(master[m])
		{
			n = 0;
			while(master[n])
			{
				i = 0;
				while (master[l][i])
				{
					j = 0;
					while (master[m][j])
					{
						k = 0;
						while (master[n][k])
						{
							if (l == 0)
							{
								write_triple_cmd_combos(fd, master[l][i], master[m][j], master[n][k]);
/*
							write(fd, master[l][i], strlen(master[l][i]));
							write(fd, " ", 1);
							write(fd, master[m][j], strlen(master[m][j]));
							write(fd, " ", 1);
							write(fd, master[n][k], strlen(master[n][k]));
*/								write(fd, "\n", 1);
							}
							k++;
						}
						j++;
					}
					i++;
				}
				n++;
			}
			m++;
		}
		l++;
	}
	close(fd);
	return (0);
}

char 	*build_quad_cmd_str(char *src1, char *src2)
{
	char *ret;
	char *tmp;

	ret = ft_strjoin(src1, " ");
	tmp = ret;
	ret = ft_strjoin(ret, src2);
	free(tmp);
	return (ret);
}

char	*quad_cmd_combos2(char **master[4], char *cmd_str)
{
	char *tmp;
	int i;
	int j;
	int k;
	int l;

	k = 0;
	while (master[k])
	{
		l = 0;
		while (master[l])
		{
			i = 0;
			while (master[k][i])
			{
				j = 0;
				while (master[l][j])
				{
					tmp = cmd_str;
					cmd_str = build_quad_cmd_str(cmd_str, master[k][i]);
					free(tmp);
					tmp = cmd_str;
					cmd_str = build_quad_cmd_str(cmd_str, master[l][j]);
					free(tmp);
					j++;
				}
				i++;
			}
			l++;
		}
		k++;
	}
	return (cmd_str);
}

int		quad_cmd_combos()
{
	char **master[4];
	int fd;
	int i;
	int j;
	int k;
	int l;
	char complete_path[66];
	char *complete_cmd;
	char *tmp;

	master[0] = cmds;
	master[1] = operators;
	master[2] = file_args;
	master[3] = NULL;
	bzero(complete_path, 66);
	strcpy(complete_path, path);
	strcat(complete_path, "quad_cmd_file");
	printf("path = %s\n", complete_path);
	fd = open(complete_path, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (fd < 0)
		return (-1);
	k = 0;
	while (master[k])
	{
		l = 0;
		while (master[l])
		{
			i = 0;
			while (master[k][i])
			{
				j = 0;
				while (master[l][j])
				{
					complete_cmd = build_quad_cmd_str(master[k][i], master[l][j]);
					tmp = complete_cmd;
					complete_cmd = quad_cmd_combos2(master, complete_cmd);
					free(tmp);
					j++;
				}
				i++;
			}
			l++;
		}
		k++;
	}
	write(fd, complete_cmd, strlen(complete_cmd));
	close(fd);
	return (0);
}

int main(void)
{
	if (simple_cmd_combos() || double_cmd_combos() || triple_cmd_combos())
		return (1);
/*
	int i;
	int n;
	time_t t;

	n = 5;
	srand((unsigned) time(&t));

	for( i = 0 ; i < n ; i++ ) 
	{
		printf("%d\n", rand() % 50);
	}
*/


return (0);
}