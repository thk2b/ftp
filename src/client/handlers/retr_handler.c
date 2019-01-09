#include		<client.h>
#include		<protocol.h>

#include		<unistd.h>
#include		<fcntl.h>
#include		<errno.h>
#include		<sys/stat.h>
#include		<io.h>

static int		do_retr(int ccon, int *dcon, int fd, char *filename)
{
	int	res_status;
	int	status;

	if ((res_status = get_response(ccon, NULL)) <= 0)
		return (res_status);
	if (res_status >= 400)
		return (0);
	if (res_status == 150 && (status = init_data_connection(ccon, dcon)))
		return (status);
	if (read_file(*dcon, fd))
		return (error(1, "read_file"));
	if (res_status == 227 || (res_status < 200 && (res_status = get_response(ccon, NULL)) == 227))
	{
		close(*dcon);
		*dcon = -1;
	}
	if (res_status >= 400 || res_status < 0)
		unlink(filename);
	return (res_status == -1 ? -1 : 0);
}

int				retr_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	char		*filename;
	int			fd;
	int			status;

	(void)ctx;
	filename = req->args[req->args[2] ? 2 : 1];
	status = 0;
	if ((send_request(ccon, req)))
		return (1);
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0775)) == -1)
		return (error(1, "open %s", filename));
	if ((status = do_retr(ccon, dcon, fd, filename)))
		unlink(filename);
	close(fd);
	return (status);
}
