#include		<client.h>
#include		<protocol.h>

#include		<unistd.h>
#include		<fcntl.h>
#include		<errno.h>
#include		<sys/stat.h>
#include		<sys/mman.h>

int				stor_handler(int ccon, int *dcon, t_request_ctx *req)
{
	int			fd;
	void		*file;
	struct stat	sb;
	int			res_status;
	int			status;

	status = 0;
	if (stat(req->args[1], &sb) == -1)
		return (error(errno, "stat"));
	if ((fd = open(req->args[1], O_RDONLY)) == -1)
		return (error(errno, "open"));
	if ((send_request(ccon, req)))
		return (1);
	if ((res_status = get_response(ccon, NULL)) == -1)
		return (1);
	if (res_status != 125 && res_status != 150)
		return (error(1, "invalid response from server")); // not an actual error?
	if (res_status == 150)
		status = init_data_connection(ccon, dcon);
	if ((file = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (error(errno, "mmap"));
	if (status == 0 && write(*dcon, file, sb.st_size) != sb.st_size)
		return (error(errno, "write"));
	info("send file");
	munmap(file, sb.st_size);
	if (get_response(ccon, NULL) == 227)
		close(fd);
	return (0);
}
