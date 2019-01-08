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
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (error(1, "socket"));
	if ((fd = init_passive_data_connection(ccon, &fd)) < 0)
	{
		close(fd);
		return (1);
	}
	//TODO: verify that the same client connected
	len = sizeof(struct sockaddr_in);
	*dcon = accept(fd, (struct sockaddr*)&addr, &len);
	close(fd);
	if (*dcon == -1)
		return (error(1, "accept"));
	info("opened data connection with %s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
	return (0);
}
