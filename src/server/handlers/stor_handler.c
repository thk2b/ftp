#include		<server.h>
#include		<protocol.h>

#include		<fcntl.h>
#include		<unistd.h>
#include		<errno.h>

static int		read_file(int from, int to)
{
	char	buf[BUF_SIZE];
	ssize_t	nr;

	info("reading from data connection, writing file");
	nr = BUF_SIZE;
	while (nr > 0)
	{
		if ((nr = read(from, buf, BUF_SIZE)) == -1)
			return (error(1, "read"));
		if (write(to, buf, nr) != nr)
			return (error(1, "write"));
	}
	info("finished writing file");
	return (0);
}

static int		do_stor(int ccon, int *dcon, int fd)
{
	if (*dcon == -1)
	{
		if (send_response(150, ccon) || pasv_handler(ccon, dcon, NULL, NULL))
			return (error(425, "couldn't setup data connection"));
	}
	else if (send_response(125, ccon))
		return (451);
	return (read_file(*dcon, fd));
}

int				stor_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	int		response_status;
	char	*filename;
	int		fd;

	(void)ctx;
	filename = req->args[req->args[2] ? 2 : 1];
	if ((fd = open(filename, O_WRONLY | O_CREAT, 0775)) == -1)
		return (error_conn(ccon, 451, 1, "open"));
	response_status = do_stor(ccon, dcon, fd);
	close(fd);
	close(*dcon);
	*dcon = -1;
	if (response_status == 0)
		return (send_response(226, ccon));
	return (send_response(response_status, ccon));
}
