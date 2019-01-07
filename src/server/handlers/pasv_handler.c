#include	<server.h>
#include	<arpa/inet.h>
#include	<sys/socket.h>
#include	<errno.h>
#include	<string.h>
#include	<stdio.h>
#include	<unistd.h>

int			pasv_handler(int ccon, int *dcon, t_request_ctx *req)
{
	int					fd;
	struct sockaddr_in	addr;
	socklen_t			len;

	(void)req;
	info("attempting to open data connection");
	if ((fd = init_passive_data_connection(ccon)) < 0)
		return (1);
	//TODO: verify that the same client connected
	len = sizeof(struct sockaddr_in);
	if ((*dcon = accept(fd, (struct sockaddr*)&addr, &len)) < 0)
		return (error(errno, "accept"));
	close(fd);
	info("opened data connection with %s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
	return (0);
}
