#include		<server.h>
#include		<protocol.h>

#include		<fcntl.h>
#include		<unistd.h>
#include		<errno.h>

static int		read_file(int from, int to)
{
	char		buf[BUF_SIZE];
	ssize_t		num_read;

	info("reading data connection, creating file");
	while ((num_read = read(from, buf, BUF_SIZE)) > 0)
	{
		if (write(to, buf, num_read) != num_read)
			return (error(451, "write"));
		if (num_read != BUF_SIZE)
			break ;
	}
	if (num_read == -1)
		return (error(451, "read"));
	return (0);
}

//TODO: send 451 instead of 550
static int		do_stor(int ccon, int *dcon, t_request_ctx *req)
{
	int			fd;
	int			status;

	status = 0;
	if (*dcon == -1)
	{
		if (send_response(150, ccon) || pasv_handler(ccon, dcon, NULL))
			return (error(425, "couldn't setup data connection"));
	}
	else if (send_response(125, ccon))
		return (1);
	if ((fd = open(req->args[req->args[2] ? 2 : 1], O_WRONLY | O_CREAT, 0775)) == -1)
		status = error(550, "open");
	if (status == 0)
		status = read_file(*dcon, fd);
	close(fd);
	return (status);
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
