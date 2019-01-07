#include	<server.h>
#include	<arpa/inet.h>
#include	<sys/socket.h>
#include	<errno.h>
#include	<string.h>
#include	<stdio.h>
#include	<unistd.h>

static int	init_passive_data_connection(int ccon)
{
	struct sockaddr_in	addr;
	int					fd;
	char				buf[26] = {0};

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (error(-1, "socket"));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = 0;
	if (bind(fd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0)
		return (error(-1, "bind"));
	if (listen(fd, 0) < 0)
		return (error(-1, "listen"));
	info("opened data connection at %s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
	if (format_addr((char*)buf, &addr))
		return (1);
	if (send_response_data(227, ccon, (char*)buf))
		return (1);
	return (fd);
}

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
	return (1);
}
