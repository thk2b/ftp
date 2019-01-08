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

	if ((file = mmap(NULL, sb->st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (error(errno, "mmap"));
	if (write(to, file, sb->st_size) != sb->st_size)
		return (error(errno, "write"));
	info("wrote file");
	if (munmap(file, sb->st_size) == -1)
		return (error(errno, "munmap"));
	return (0);
}

int				stor_handler(int ccon, int *dcon, t_request_ctx *req)
{
	int			fd;
	struct stat	sb;
	int			res_status;
	int			status;

	status = 0;
	if (stat(req->args[1], &sb) == -1)
		return (error(errno, "stat"));
	if (!S_ISREG(sb.st_mode))
		return (error(1, "\"%s\" is not a regular file", req->args[1]));
	if ((fd = open(req->args[1], O_RDONLY)) == -1)
		return (error(errno, "open"));
	if ((send_request(ccon, req)))
		return (1);
	if ((res_status = get_response(ccon, NULL)) <= 0)
		return (res_status);
	if (res_status != 125 && res_status != 150)
		return (error(0, "invalid response from server"));
	if (res_status == 150)
		status = init_data_connection(ccon, dcon);
	if (status == 0)
		status = write_file(*dcon, fd, &sb);
	close(fd);
	if (get_response(ccon, NULL) == 227)
		close(*dcon);
	return (status);
}
