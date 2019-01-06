#include	<server.h>
#include	<stdio.h>
#include	<libft.h>
#include	<errno.h>

int			send_response(int code, int con)
{
	t_response	*res;

	res = find_response(code);
	if (dprintf(con, "%3.3d %s\r\n", res->code, res->message) != 6 + (int)res->message_len)
		return (error(errno, "dprintf"));
	info("sent \"%3.3d %s\"", res->code, res->message);
	return (0);
}
