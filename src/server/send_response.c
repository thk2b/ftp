#include	<server.h>
#include	<stdio.h>
#include	<libft.h>
#include	<errno.h>

int			send_response(int code, int con)
{
	t_response	*res;
	// char		numbuf[4] = {0};
	// size_t		numlen;

	res = find_response(code);
	if (dprintf(con, "%3.3d %s\r\n", res->code, res->message) != 6 + (int)res->message_len)
		return (error(errno, "dprintf"));
	info("sent \"%3.3d %s\"", res->code, res->message);
	return (0);
	// numlen = snprintf(numbuf, 4, "%d", res->code);
	// if (write(con, numbuf, numlen) == (unsigned)numlen
	// && write(con, res->message, res->message_len) == (unsigned)res->message_len)
	// {
	// }
}
