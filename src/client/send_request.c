#include	<client.h>
#include	<string.h>
#include	<errno.h>
#include	<unistd.h>
#include	<stdio.h>

/*
**	send a request to the server
**		return 0 if success, 1 on error.
*/
int			send_request(int ccon, t_request_ctx *req)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (req->args[i])
	{
		len = strlen(req->args[i]);
		if (dprintf(ccon, "%s ", req->args[i]) != (int)len + 1)
			return (error(-1, "dprintf"));
		i++;
	}
	if (write(ccon, "\r\n", 2) != 2)
		return (error(-1, "write"));
	return (0);
}

// TODO: buffer request
// int			send_request(int ccon, t_request_ctx *req)
// {
// 	size_t	i;
// 	char	buf[BUF_SIZE] = {0};
// 	size_t	bi;
// 	size_t	len;

// 	i = 0;
// 	bi = 0;
// 	while (req->args[i])
// 	{
// 		while (req->args[i])
// 		{
// 			len = strlen(req->args[i]);
// 			if (bi + len + 1 > BUF_SIZE - 2)
// 				break ;
// 			memcpy(buf + bi, req->args[i], len);
// 			bi += len;
// 			buf[bi++] = ' ';
// 			i++;
// 		}
// 		memcpy(buf + bi, "\r\n", 2);
// 		info("\"sending %s\"", buf);
// 		if (write(ccon, buf, bi + 2) != (unsigned)bi + 2)
// 			return (error(errno, "write"));
// 		bi = 0;
// 	}
// 	return (0);
// }
