#include		<server.h>
#include		<protocol.h>

#include		<fcntl.h>
#include		<unistd.h>
#include		<errno.h>

static int		do_stor(int ccon, int *dcon, t_request_ctx *req)
{
	int			fd;
	char		buf[BUF_SIZE];
	ssize_t		num_read;

	if (*dcon == -1)
	{
		if (send_response(150, ccon) || pasv_handler(ccon, dcon, NULL))
			return (error(425, "couldn't setup data connection"));
	}
	else if (send_response(125, ccon))
		return (1);
	if ((fd = open(req->args[req->args[2] ? 2 : 1], O_WRONLY | O_CREAT, 0775)) == -1)
		return (error(550, "open"));
	info("reading data connection, creating file");
	while ((num_read = read(*dcon, buf, BUF_SIZE)) > 0)
	{
		if (write(fd, buf, num_read) != num_read)
			return (error(550, "write"));
		if (num_read != BUF_SIZE)
			break ;
	}
	if (num_read == -1)
		return (error(550, "read"));
	return (0);
}

int				stor_handler(int ccon, int *dcon, t_request_ctx *req)
{
	int		should_close_dcon;
	int		response_status;

	should_close_dcon = *dcon == -1;
	response_status = do_stor(ccon, dcon, req);
	if (should_close_dcon)
	{
		close(*dcon);
		*dcon = -1;
	}
	if (response_status == 0)
		return (send_response(should_close_dcon ? 226 : 250, ccon));
	return (send_response(response_status, ccon));
}
