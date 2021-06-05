%:include <stdio.h>

void	foo(void)
<%
	printf("Hello World");
%>

int	main(int argc, char **argv)
<%
	char tab<::> = "Hello World\n";
	printf("%s", tab);
	return (0);
%>
