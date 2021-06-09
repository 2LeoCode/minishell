#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	int pipefd[2]; // pipefd[0] for read and pipefd[1] for write
	char	c;
	pid_t	cpid;

	for (int i = 1; i < argc; i++) {
		pipe(pipefd);
		cpid = fork();
		if (!cpid) {
			close(pipefd[0]);
			dup2(pipefd[1], 1);
			write(1, argv[i], strlen(argv[i]));
			return (0);
		} else {
			close(pipefd[1]);
			write(1, "pipe:", 5);
			while (read(pipefd[0], &c, 1))
				write(1, &c, 1);
			write(1, "\n", 1);
		}
	}
	return (0);
}
