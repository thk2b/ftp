#include	<server.h>

#include	<errno.h>
#include	<unistd.h>
#include	<sys/socket.h>
#include	<arpa/inet.h>

int			init(int *lconp, t_opts *opts)
{
	int					sock;
	struct sockaddr_in	addr;
	int					reuse_addr;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (error(1, "socket"));
	addr.sin_family = AF_INET;
	addr.sin_port = htons((uint16_t)opts->port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	info("attempting to bind to %s:%d", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	reuse_addr = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(int)) < 0)
		return (error(1, "setsockopt"));
	if ((bind(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_in))) < 0)
		return (error(1, "bind"));
	if (listen(sock, BACKLOG) < 0)
		return (error(1, "listen"));
	info("listening for connections on %s:%d", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	*lconp = sock;
	return (0);
}

int			init_passive_data_connection(int ccon, int *dcon)
{
	struct sockaddr_in	addr;
	socklen_t			len;
	int					fd;
	char				buf[26] = {0};
	int					reuse_addr;

	fd = *dcon;
	reuse_addr = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (void*)&reuse_addr, sizeof(int)))
		return (error(-1, "setsockopt"));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = 0;
	if (bind(fd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0)
		return (error(-1, "bind"));
	if (listen(fd, 0) < 0)
		return (error(-1, "listen"));
	len = sizeof(struct sockaddr_in);
	if (getsockname(fd, (struct sockaddr*)&addr, &len) < 0)
		return (error(-1, "gesockname"));
	if (inet_aton(PUBLIC_IP, &addr.sin_addr) != 1)
		return (error(-1, "inet_atoi(PUBLIC_IP)"));
	info("opened data connection at %s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
	if (format_addr((char*)buf, &addr))
		return (-1);
	if (send_response_data(227, ccon, (char*)buf))
		return (-1);
	return (fd);
}
