#include	<server.h>
#include	<arpa/inet.h>
#include	<sys/socket.h>
#include	<errno.h>
#include	<string.h>
#include	<stdio.h>
#include	<unistd.h>

int			pasv_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	int					fd;
	struct sockaddr_in	addr;
	socklen_t			len;
//	t_client			*client;

	(void)req;
	(void)ctx;
//	client = (t_client*)ctx;
	info("attempting to open data connection");
	if (*dcon >= 0)
		close(*dcon);
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (error(1, "socket"));
	if ((fd = init_passive_data_connection(ccon, &fd)) < 0)
	{
		close(fd);
		return (1);
	}
	len = sizeof(struct sockaddr_in);
	// while((*dcon = accept(fd, (struct sockaddr*)&addr, &len)))
	// {
		// if (addr.sin_addr.s_addr == client->addr.sin_addr.s_addr)
		// 	break;
		// close(*dcon);
		// info("a different client connected to the data connection");
	// }
	if((*dcon = accept(fd, (struct sockaddr*)&addr, &len)) == -1)
		return (error(1, "accept"));
	close(fd);
	info("opened data connection with %s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
	return (0);
}
