#include	<client.h>
#include	<libft.h>
#include	<errno.h>
#include	<string.h>
#include	<stdio.h>

int			run(int ccon)
{
	extern t_request	g_protocol[];
	extern t_cmd		g_commands[];
	t_request_ctx		req;
	int					status;
	int					dcon;

	status = 0;
	if (get_response(ccon, NULL) != 220)
		status = 1;
	dcon = -1;
	while (status != -1)
	{
		errno = 0;
		if (get_request(&req, 0))
			continue ;
		if (req.args[1] && strcmp(req.args[1], "--help") == 0)
			usage_error(g_commands[req.rid].help, &g_commands[req.rid].name);
		else
			status = g_protocol[req.rid].fn(ccon, &dcon, &req);
		ft_strvdel(req.args);
	}
	close(ccon);
	if (dcon >= 0)
		close(dcon);
	return (status == -1 ? 0 : status);
}
