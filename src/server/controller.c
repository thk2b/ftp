#include	<server.h>
#include	<unistd.h>
#include	<errno.h>
#include	<libft.h>
#include	<stdio.h>

int			controller(int ccon)
{
	extern t_request	g_protocol[];
	t_request_ctx		req;
	int					go;
	int					dcon;
	int					status;

	send_response(220, ccon);
	go = 1;
	dcon = -1;
	while (go)
	{
		errno = 0;
		if ((status = get_request(&req, ccon)) == -1)
			break ;
		if (status != 0)
		{
			send_response(status, ccon);
			continue ;
		}
		go = g_protocol[req.rid].fn(ccon, &dcon, &req);
		ft_strvdel(req.args);
	}
	return (errno);
}
