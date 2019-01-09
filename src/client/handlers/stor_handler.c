#include		<client.h>
#include		<protocol.h>

#include		<unistd.h>
#include		<fcntl.h>
#include		<errno.h>
#include		<sys/stat.h>
#include		<io.h>

static int		do_stor(int ccon, int *dcon, int fd, struct stat *sb)
{
	int			res_status;

	if ((res_status = get_response(ccon, NULL)) <= 0)
		return (-1);
	if (res_status != 125 && res_status != 150)
		return (error(1, "invalid response from server"));
	if (res_status == 150 && init_data_connection(ccon, dcon))
		return (1);
	if (write_file(*dcon, fd, sb))
		return (error(1, "write_file"));
	return (0);
}

int				stor_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	int			fd;
	struct stat	sb;
	int			status;

	(void)ctx;
	if (stat(req->args[1], &sb) == -1)
		return (error(1, "stat"));
	if (!S_ISREG(sb.st_mode))
		return (error(1, "\"%s\" is not a regular file", req->args[1]));
	if ((status = send_request(ccon, req)))
		return (status);
	if ((fd = open(req->args[1], O_RDONLY)) == -1)
		return (error(errno, "open"));
	status = do_stor(ccon, dcon, fd, &sb);
	close(fd);
	close(*dcon);
	*dcon = -1;
	if (status == 0)
		status = get_response(ccon, NULL);
	return (status);
}
