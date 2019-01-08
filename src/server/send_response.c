#include	<server.h>
#include	<stdio.h>
#include	<libft.h>
#include	<errno.h>
#include	<string.h>

int			send_response(int code, int con)
{
	t_response	*res;

	res = find_response(code);
	if (dprintf(con, "%3.3d %s\r\n", res->code, res->message) != 6 + (int)res->message_len)
		return (error(1, "dprintf"));
	info("sent \"%3.3d %s\"", res->code, res->message);
	return (0);
}

int			send_response_data(int code, int con, char *data)
{
	t_response	*res;

	res = find_response(code);
	if (dprintf(con, "%3.3d %s %s\r\n", res->code, res->message, data) != 6 + (int)res->message_len + (int)strlen(data) + 1)
		return (error(1, "dprintf"));
	info("sent \"%3.3d %s %s\"", res->code, res->message, data);
	return (0);
}
