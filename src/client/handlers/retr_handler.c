#include		<client.h>
#include		<protocol.h>

#include		<unistd.h>
#include		<fcntl.h>
#include		<errno.h>
#include		<sys/stat.h>

static int		read_file(int from, int to)
{
	char	buf[BUF_SIZE];
	ssize_t	nr;

	info("reading from data connection, writing file");
	nr = BUF_SIZE;
	while (nr == BUF_SIZE)
	{
		if ((nr = read(from, buf, BUF_SIZE)) == -1)
			return (error(1, "read"));
		if (write(to, buf, nr) != nr)
			return (error(1, "write"));
	}
	info("finished writing file");
	return (0);
}

int				retr_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	char		*filename;
	int			fd;
	int			res_status;
	int			status;

	(void)ctx;
	filename = req->args[req->args[2] ? 2 : 1];
	status = 0;
	res_status = 0;
	if ((send_request(ccon, req)))
		return (1);
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0775)) == -1)
		return (error(1, "open %s", filename));
	if (status == 0 && (res_status = get_response(ccon, NULL)) <= 0)
		status = 1;
	if (res_status >= 400)
		status = 1;
	if (status == 0 && res_status == 150)
		status = init_data_connection(ccon, dcon);
	if (status == 0)
		read_file(*dcon, fd);
	if (res_status == 227 || (res_status < 200 && (res_status = get_response(ccon, NULL)) == 227))
	{
		close(*dcon);
		*dcon = -1;
	}
	if (status || res_status >= 400)
		unlink(filename);
	close(fd);
	return (status);
}
