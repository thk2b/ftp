#include	<server.h>
#include	<unistd.h>
#include	<errno.h>
#include	<libft.h>
#include	<stdio.h>
#include	<string.h>

static int	set_sock_timeout(int fd)
{
	struct timeval	tv;

	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;
	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(struct timeval)))
		return (error(1, "setsockopt(RCVTIMEO)"));
	return (0);
}

int			controller(int ccon, t_client *client)
{
	t_request_ctx		req;
	int					error_code;
	int					dcon;
	int					status;

	status = 0;
	set_sock_timeout(ccon);
	if (send_response(220, ccon))
		status = -1;
	dcon = -1;
	while (status != -1)
	{
		errno = 0;
		if ((error_code = get_request(&req, ccon)) == -1)
			break ;
		if (error_code != 0)
		{
			send_response(error_code, ccon);
			continue ;
		}
		status = call_handler(ccon, &dcon, &req, client);
		ft_strvdel(req.args);
	}
	return (status != 0);
}
