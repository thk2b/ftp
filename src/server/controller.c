#include	<server.h>
#include	<unistd.h>
#include	<errno.h>
#include	<libft.h>
#include	<stdio.h>

int			controller(int ccon)
{
	extern t_request	g_protocol[];
	t_request_ctx		req;
	int					error_code;
	int					dcon;
	int					status;

	if (send_response(220, ccon))
		status = 1;
	status = 0;
	dcon = -1;
	while (status == 0)
	{
		errno = 0;
		if ((error_code = get_request(&req, ccon)) == -1)
			break ;
		if (error_code != 0)
		{
			send_response(error_code, ccon);
			continue ;
		}
		status = g_protocol[req.rid].fn(ccon, &dcon, &req);
		ft_strvdel(req.args);
	}
	return (status);
}
