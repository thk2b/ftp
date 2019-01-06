#include	<client.h>
#include	<libft.h>
#include	<get_next_line.h>
#include	<errno.h>
#include	<string.h>
#include	<stdio.h>

static int	accept_greeting(int conn)
{
	char	*line;
	int		status;

	if ((status = get_next_line(conn, &line)) == -1)
		return (error(errno, "get_next_line"));
	puts(line);
	return (0);
}

int			run(int ccon)
{
	extern t_request	g_protocol[];
	t_request_ctx		req;
	int					go;
	int					dcon;

	if (accept_greeting(ccon))
		return (1);
	go = 1;
	dcon = -1;
	while (go)
	{
		errno = 0;
		if (get_request(&req, 0))
			continue ;
		go = g_protocol[req.rid].fn(ccon, &dcon, &req);
		ft_strvdel(req.args);
	}
	return (0);
}
