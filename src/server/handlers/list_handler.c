#include		<server.h>
#include		<protocol.h>
#include		<io.h>

#include		<errno.h>
#include		<unistd.h>

static int		do_list(int ccon, int *dcon, char *filename)
{
	if (*dcon == -1)
	{
		if (send_response(150, ccon) || pasv_handler(ccon, dcon, NULL, NULL))
			return (error(425, "couldn\'t open data connection"));
	}
	else if (send_response(125, ccon))
		return (1);
	return (list(filename, *dcon));
}

int				list_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	char	*path;
	int		status;

	(void)ctx;
	path = req->args[1] ? req->args[1] : ".";
	status = do_list(ccon, dcon, path);
	close(*dcon);
	*dcon = -1;
	if (status == -1)
		return (send_response(550, ccon));
	else if (status)
		return (send_response(451, ccon));
	return (send_response(226, ccon));
}
