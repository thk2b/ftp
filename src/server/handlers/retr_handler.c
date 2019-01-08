#include		<server.h>
#include		<protocol.h>

#include		<unistd.h>
#include		<fcntl.h>
#include		<sys/stat.h>
#include		<errno.h>
#include		<sys/mman.h>

static int		write_file(int to, int fd, struct stat *sb)
{
	void	*file;

	if (sb->st_size == 0)
		return (0);
	if ((file = mmap(NULL, sb->st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (error(1, "mmap"));
	if (write(to, file, sb->st_size) != sb->st_size)
		return (error(1, "write"));
	info("wrote file");
	if (munmap(file, sb->st_size) == -1)
		return (error(1, "munmap"));
	return (0);
}

static int		do_retr(int ccon, int *dcon, t_request_ctx *req)
{
	int			fd;
	struct stat	sb;
	char		*filename;
	int			status;

	filename = req->args[1];
	if (stat(filename, &sb) == -1)
		return (error(550, "stat"));
	if (!S_ISREG(sb.st_mode))
		return (error(550, "\"%s\" is not a regular file", filename));
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (error(451, "open"));
	if (*dcon == -1)
	{
		if ((status = send_response(150, ccon)) == 0)
			status = pasv_handler(ccon, dcon, NULL, NULL);
		if (status)
		{
			close(fd);
			return (error(425, "couldn\'t open data connection"));
		}
	}
	status = write_file(*dcon, fd, &sb) ? 451 : 0;
	close(fd);
	return (status);
}

int				retr_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{	
	int		should_close_dcon;
	int		response_status;

	(void)ctx;
	should_close_dcon = *dcon == -1;
	response_status = do_retr(ccon, dcon, req);
	if (should_close_dcon)
	{
		close(*dcon);
		*dcon = -1;
	}
	if (response_status == 0)
		return (send_response(should_close_dcon ? 226 : 250, ccon));
	return (send_response(response_status, ccon));

}
