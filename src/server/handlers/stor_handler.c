#include		<server.h>
#include		<protocol.h>

#include		<fcntl.h>
#include		<unistd.h>
#include		<errno.h>
#include		<io.h>

static int		do_stor(int ccon, int *dcon, int fd)
{
	if (*dcon == -1)
	{
		if (send_response(150, ccon) || pasv_handler(ccon, dcon, NULL, NULL))
			return (error(425, "couldn't setup data connection"));
	}
	else if (send_response(125, ccon))
		return (451);
	if (read_file(*dcon, fd))
		return (error(1, "read_file"));
	return (0);
}

int				stor_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	int		response_status;
	char	*filename;
	int		fd;

	(void)ctx;
	filename = req->args[req->args[2] ? 2 : 1];
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0775)) == -1)
		return (error_conn(ccon, 451, 1, "open"));
	response_status = do_stor(ccon, dcon, fd);
	close(fd);
	close(*dcon);
	*dcon = -1;
	if (response_status == 0)
		return (send_response(226, ccon));
	return (send_response(response_status, ccon));
}
