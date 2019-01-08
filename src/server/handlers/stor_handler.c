#include		<server.h>
#include		<protocol.h>

#include		<fcntl.h>
#include		<unistd.h>
#include		<errno.h>

int				stor_handler(int ccon, int *dcon, t_request_ctx *req)
{
	int			fd;
	char		buf[BUF_SIZE];
	ssize_t		num_read;

	if (*dcon == -1)
	{
		if (send_response(150, ccon) || pasv_handler(ccon, dcon, NULL))
			return (error(1, "couldn't setup data connection"));
	}
	else if (send_response(125, ccon))
		return (1);
	if ((fd = open(req->args[1], O_WRONLY | O_CREAT, 775)) == -1)
		return (error_conn(ccon, 550, errno, "open"));
	info("reading data connection, creating file");
	while ((num_read = read(*dcon, buf, BUF_SIZE)) > 0)
	{
		if (write(fd, buf, num_read) != num_read)
			return (error_conn(ccon, 550, errno, "write"));
		if (num_read != BUF_SIZE)
			break ;
	}
	if (num_read == -1)
		return (error_conn(ccon, 550, errno, "read"));
	close(*dcon);
	*dcon = -1;
	send_response(226, ccon);
	return (0);
}
