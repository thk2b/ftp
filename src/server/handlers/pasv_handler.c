#include	<server.h>
#include	<arpa/inet.h>
#include	<sys/socket.h>
#include	<errno.h>
#include	<string.h>
#include	<stdio.h>
#include	<unistd.h>

static int	set_sock_opts(int fd)
{
	int				reuse_addr;
	struct timeval	tv;

	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;
	if (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, (void*)&tv, sizeof(struct timeval)))
		return (error(1, "setsockopt(RCVTIMEO)"));
	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (void*)&tv, sizeof(struct timeval)))
		return (error(1, "setsockopt(RCVTIMEO)"));
	reuse_addr = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (void*)&reuse_addr, sizeof(int)))
		return (error(1, "setsockopt"));
	return (0);
}

static int		init_passive_data_connection(int ccon, int lcon)
{
	struct sockaddr_in	addr;
	socklen_t			len;
	char				buf[30] = {0};
	extern t_opts		g_opts;

	addr.sin_family = AF_INET;
	addr.sin_port = 0;
	addr.sin_addr.s_addr = g_opts.ip;
	if (bind(lcon, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0)
		return (error(-1, "bind"));
	if (listen(lcon, 0) < 0)
		return (error(-1, "listen"));
	len = sizeof(struct sockaddr_in);
	if (getsockname(lcon, (struct sockaddr*)&addr, &len) < 0)
		return (error(-1, "gesockname"));
	info("opened data connection at %s:%d", inet_ntoa(addr.sin_addr), htons(addr.sin_port));
	if (format_addr((char*)buf, &addr))
		return (-1);
	if (send_response_data(227, ccon, (char*)buf))
		return (-1);
	return (0);
}

int			pasv_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	int					fd;
	struct sockaddr_in	addr;
	socklen_t			len;
	t_client			*client;

	(void)req;
	client = (t_client*)ctx;
	info("attempting to open data connection");
	if (*dcon >= 0)
		close(*dcon);
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (error(1, "socket"));
	set_sock_opts(fd);
	if ((init_passive_data_connection(ccon, fd)))
	{
		close(fd);
		return (1);
	}
	len = sizeof(struct sockaddr_in);
	while((*dcon = accept(fd, (struct sockaddr*)&addr, &len)))
	{
		if (addr.sin_addr.s_addr == client->addr.sin_addr.s_addr)
			break;
		close(*dcon);
		info("a different client connected to the data connection");
	}
	set_sock_opts(*dcon);
	close(fd);
	info("opened data connection with %s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
	return (0);
}
