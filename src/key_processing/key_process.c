#include <minishell.h>
/*
**	In that function we have our data structures and the last key that has been
**	pressed. So we will check for every "action" keys (ENTER, arrow keys, and
**	DEL key), or if the key is a printable character that we can display, and
**	then we call different function and return different values:
**	If the key value is -1, it will mean that an error occurred in our
**	`ft_getchar` function (so `read` returned -1), or if an allocation failed,
**	we will return -1, else we will return 1 only if `key` is ENTER to inform
**	that the command has been sent to the program, otherwise we will return 0.
*/
static int	process_key(t_shell *ms, t_input *input, int key)
{
	if (g_global_data.sigint)
		handle_sigint(input);
	if (key == _KEY_TAB || key == _KEY_EOF)
		return (2 * (key == _KEY_EOF));
	if (key == _KEY_ENTER)
		return (1);
	if (key == -1 || (ft_isprint(key) && process_key_print(input, key)))
		return (-1);
	else if (key == _KEY_DELETE)
	{
		if (!input->index)
			return (0);
		if (process_key_del(input))
			return (-1);
	}
	else if (key == _KEY_LEFT)
		return (process_key_left(&ms->tcaps, input));
	else if (key == _KEY_RIGHT)
		return (process_key_right(&ms->tcaps, input));
	else if ((key == _KEY_UP) || (key == _KEY_DOWN))
		if (process_key_hist(g_global_data.history, input,
					key) == -1)
			return (-1);
	return (update_input(&ms->tcaps, input));
}

/*
**	The function to handle input in non-canonical mode (to be able to move the
**	cursor and to have a command history):
**	We have our input struct that we setup with default values (the cursor index
**	is 0 at the beginning as well as the history pointer initially points to the
**	last command in history), we then call our `process_key` function (see
**	above), we send it our main struct ms, the address of our input struct to be
**	able to edit it, and the key which is pressed through a custom `ft_getchar`
**	function that handles non ascii keys that wee need such as ENTER, LEFT, ...
**	(see libft for `ft_getchar`). `process_key` will return 1 when the ENTER key
**	is pressed, otherwise it will return 0, so we loop on that function until it
**	returns a non null value to process every key one by one.
**	Then we check if the return value is -1, which means that an error occured,
**	in that case we will just free the input string (`input.in`), else we write
**	a new line and we put the input in `*final_input` string.
**	We then return `ret` which is the last return value of `process_key` (-1 on
**	failure or 1 on success)
*/
int	get_input(t_shell *ms, char **final_input)
{
	t_input		input;
	int			ret;

	input.in = ft_strdup("");
	if (!input.in)
		return (-1);
	input.index = 0;
	input.prev_index = 0;
	input.hist = g_global_data.history;
	input.prev_len = 0;
	ret = 0;
	while (!ret)
		ret = process_key(ms, &input, ft_getchar());
	if (ret == -1)
		free(input.in);
	else
	{
		write(1, "\n", 1);
		*final_input = input.in;
	}
	return (ret);
}
