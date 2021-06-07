%:include <stdio.h>
%:include <limits.h>

%:define concat(h, e, l, _l, o, _, w, _o, r, _l_, d) _ ## h ## r ## l
%:define magic concat(a, b, n, o, r, m, _a, l, i, t, y)
%:define magical_trick concat(e, w, t, f, p, _t, l, o, x, q, k)

typedef unsigned long	size_t;

int	magic(void) <%
	char _text<:14:> = "Hello World !";

	printf("%s\n", magical_trick);
	return (0);
%>
