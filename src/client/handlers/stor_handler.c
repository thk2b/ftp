#include		<client.h>
#include		<protocol.h>

#include		<unistd.h>
#include		<fcntl.h>
#include		<errno.h>
#include		<sys/stat.h>
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

static int		do_stor(int ccon, int *dcon, int fd, struct stat *sb)
{
	int			res_status;

	if ((res_status = get_response(ccon, NULL)) <= 0)
		return (1);
	if (res_status != 125 && res_status != 150)
		return (error(1, "invalid response from server"));
	if (res_status == 150 && init_data_connection(ccon, dcon))
		return (1);
	return (write_file(*dcon, fd, sb));
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
	if ((send_request(ccon, req)))
		return (1);
	if ((fd = open(req->args[1], O_RDONLY)) == -1)
		return (error(errno, "open"));
	status = do_stor(ccon, dcon, fd, &sb);
	close(fd);
	close(*dcon);
	*dcon = -1;
	get_response(ccon, NULL);
	return (status);
}
