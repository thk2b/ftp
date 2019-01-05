#include	<client.h>
#include	<libft.h>

int			run(int ccon)
{
	int					go;
	t_request			req;
	t_cmd_handler_fn	handler;

	go = 1;
	while (go)
	{
		if (get_request(&req, 0))
			error(0, "get_cmd");
		if ((handler = find_handler(&req)))
			go = handler(ccon, &req);
		else
			go = 1;
	}
	return (0);
}
