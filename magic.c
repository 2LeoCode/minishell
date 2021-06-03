%:include <stdio.h>

void	foo(void)
<%
	printf("Hello World");
%>

int	main(int argc, char **argv)
<%
	void	(*fooptr)(void) = foo;

	printf("%s\n", #foo);
	return (0);
%>