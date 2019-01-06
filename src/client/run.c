#include	<client.h>
#include	<libft.h>

int			run(int ccon)
{
	extern t_request	g_protocol[];
	t_request_ctx		req;
	int					go;
	int					dcon;

	go = 1;
	dcon = -1;
	while (go)
	{
		if (get_request(&req, 0))
			continue ;
		go = g_protocol[req.rid].fn(ccon, &dcon, &req);
		ft_strvdel(req.args);
	}
	return (0);
}
