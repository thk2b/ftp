#include		<server.h>
#include		<protocol.h>

#include		<unistd.h>
#include		<fcntl.h>
#include		<sys/stat.h>
#include		<errno.h>
#include		<sys/mman.h>
#include		<io.h>

static int		do_retr(int ccon, int *dcon, int fd, struct stat *sb)
{
	if (*dcon == -1)
	{
		if (send_response(150, ccon) || pasv_handler(ccon, dcon, NULL, NULL))
			return (error(425, "couldn\'t open data connection"));
	}
	else if (send_response(125, ccon))
		return (451);
	if (write_file(*dcon, fd, sb))
		return (error(1, "write_file"));
	return (0);
}

int				retr_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{	
	int		status;
	char	*filename;
	int		fd;
	struct stat	sb;

	(void)ctx;
	filename = req->args[1];
	if (stat(filename, &sb) == -1)
		return (error_conn(ccon, 550, 1, "stat"));
	if (!S_ISREG(sb.st_mode))
		return (error(550, "\"%s\" is not a regular file", filename));
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (error(451, "open"));
	status = do_retr(ccon, dcon, fd, &sb);
	close(fd);
	close(*dcon);
	*dcon = -1;
	if (status == 0)
		return (send_response(226, ccon));
	return (send_response(451, ccon));
}
