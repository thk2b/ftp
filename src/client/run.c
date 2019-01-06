#include	<client.h>
#include	<libft.h>

int			run(int ccon)
{
	int					go;
	int					dcon;
	t_request			req;
	t_cmd_handler_fn	handler;

	go = 1;
	dcon = -1;
	while (go)
	{
		if (get_request(&req, 0))
			continue ;
		if ((handler = find_handler(&req)))
			go = handler(ccon, &dcon, &req);
		else
			go = 1;
		ft_strvdel(req.args);
	}
	(void)ccon;
	return (0);
}
